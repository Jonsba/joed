#include "lua_vm.h"
#include "joed.h"

#include <QTextCodec>
#include <lua.hpp>

char* to_chars(QString text) {
	// Needs a pointer to a QByteArray to be explicitely created, so that it will persist after the
	// function returns. The earlier version of To_Chars caused random issues because the lambda
	// QByteArray created by the expression 'return text.toLatin1().data()' didn't persist, which
	// means that its 'char *' data returned by the function didn't persist as well.
	QByteArray* ba = new QByteArray();
	// Needs latin1 encoding for Lua
	*ba = text.toLatin1();
	return ba->data();
}

Lua_VM::Lua_VM() {
	this->L = luaL_newstate();
	luaL_openlibs(L);
}

int Lua_VM::expr_init(QString expr) {
	luaL_loadstring(this->L, to_chars("return " + expr));
	return luaL_ref(this->L, LUA_REGISTRYINDEX);
}

QString Lua_VM::expr_exec(int cookie) {
	lua_rawgeti(this->L, LUA_REGISTRYINDEX, cookie);
	lua_call(this->L, 0, 1);
	const char* result = lua_tostring(this->L, -1);
	lua_pop(this->L, 1);
	return QString::fromLatin1(result);
}

void Lua_VM::push_variable(QString key, QString value) {
	lua_pushstring(this->L, to_chars(value));
	lua_setglobal(this->L, to_chars(key));
}

void Lua_VM::push_variables(QHash<QString, QString> global_dict) {
	for (auto i = global_dict.begin(); i != global_dict.end(); i++) {
		if (i.key().contains(".")) {
			this->push_table(i.key(), i.value());
		} else {
			this->push_variable(i.key(), i.value());
		}
	}
}

void Lua_VM::push_table(QString key, QString value) {
	QStringList splitted_key = key.split(".");
	for (int i = 1; i < splitted_key.length(); i++) {
		lua_newtable(L);
		lua_pushstring(L, to_chars(splitted_key[i]));
	}
	lua_pushstring(L, to_chars(value));
	for (int i = 1; i < splitted_key.length(); i++) {
		lua_settable(L, -3);
	}
	lua_setglobal(L, to_chars(splitted_key[0]));
}
