#include "lua_vm.h"
#include "joed.h"

#include <QTextCodec>
#include <lua.hpp>

char* to_chars(QString text) {
	// The QByteArray needs to persist after the function returns. The earlier version of To_Chars
	// caused random issues because the lambda QByteArray created by the expression 'return
	// text.toLatin1().data()' didn't persist, which means that its 'char *' data returned by the
	// function didn't persist as well.
	static QByteArray ba;
	// Needs latin1 encoding for Lua
	ba = text.toLatin1();
	return ba.data();
}

Lua_VM::Lua_VM() {
	this->the_L = luaL_newstate();
	luaL_openlibs(the_L);
}

int Lua_VM::load_expr(QString expr) {
	luaL_loadstring(this->the_L, to_chars("return " + expr));
	return luaL_ref(this->the_L, LUA_REGISTRYINDEX);
}

QString Lua_VM::eval_expr(int cookie) {
	lua_rawgeti(this->the_L, LUA_REGISTRYINDEX, cookie);
	lua_call(this->the_L, 0, 1);
	const char* result = lua_tostring(this->the_L, -1);
	lua_pop(this->the_L, 1);
	return QString::fromLatin1(result);
}

void Lua_VM::push_variables(QHash<QString, QString> global_dict) {
	for (auto pair = global_dict.begin(); pair != global_dict.end(); pair++) {
		this->push_variable(pair.key(), pair.value());
	}
}

void Lua_VM::push_variable(QString variable, QString value) {
	if (variable.contains(".")) {
		this->push_table(variable, value);
	} else {
		this->push_scalar(variable, value);
	}
}

void Lua_VM::push_scalar(QString key, QString value) {
	lua_pushstring(this->the_L, to_chars(value));
	lua_setglobal(this->the_L, to_chars(key));
}

void Lua_VM::push_table(QString key, QString value) {
	QStringList splitted_key = key.split(".");
	for (int i = 1; i < splitted_key.length(); i++) {
		lua_newtable(the_L);
		lua_pushstring(the_L, to_chars(splitted_key[i]));
	}
	lua_pushstring(the_L, to_chars(value));
	for (int i = 1; i < splitted_key.length(); i++) {
		lua_settable(the_L, -3);
	}
	lua_setglobal(the_L, to_chars(splitted_key[0]));
}

lua_State* Lua_VM::L() {
	return this->the_L;
}
