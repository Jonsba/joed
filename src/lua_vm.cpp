#include "lua_vm.h"

#include <QTextCodec>
#include <lua.hpp>

char* To_Chars(QString text) {
	// Needs latin1 encoding for Lua
	return text.toLatin1().data();
}

Lua_VM::Lua_VM() {
	this->L = luaL_newstate();
	luaL_openlibs(L);
}

int Lua_VM::expr_init(QString expr) {
	luaL_loadstring(this->L, To_Chars("return " + expr));
	return luaL_ref(this->L, LUA_REGISTRYINDEX);
}

QString Lua_VM::expr_exec(int cookie) {
	lua_rawgeti(this->L, LUA_REGISTRYINDEX, cookie);
	lua_call(this->L, 0, 1);
	const char* result = lua_tostring(this->L, -1);
	lua_pop(this->L, 1);
	return QString::fromLatin1(result);
}

void Lua_VM::set_global_variable(QString key, QString value) {
	lua_pushstring(this->L, To_Chars(value));
	lua_setglobal(this->L, To_Chars(key));
}

void Lua_VM::set_global_variables(Global_Dict global_dict) {
	for (auto i = global_dict.begin(); i != global_dict.end(); i++) {
		this->set_global_variable(i.key(), i.value());
	}
}
