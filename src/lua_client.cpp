#include "lua_client.h"
#include "lua_vm.h"
#include <lua.hpp>

Lua_Client::Lua_Client(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
}

QString Lua_Client::eval(QString expr) {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->expr_init(expr);
	}
	return this->lua_vm->expr_exec(this->lua_cookie);
}

QString Lua_Client::eval(QString expr, QHash<QString, QString> global_dict) {
	this->lua_vm->set_global_variables(global_dict);
	return this->eval(expr);
}
