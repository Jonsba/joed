#include "lua_vm.h"
#include "joed.h"

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
	// If expr value is a plain joed variable (e.g. _text_content_), then an error will strangely be
	// most of the time thrown, while executing the expression with lua_call in expr_exec method.
	// To fix this, 'return '' .. expr .. ''' will work, or better: using table.concat
	luaL_loadstring(this->L, To_Chars("return table.concat({" + expr + "})"));
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
