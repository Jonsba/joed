#include "lua_client.h"
#include "lua_vm.h"
#include <lua.hpp>

Lua_Client::Lua_Client(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
	this->output = "";
}

void Lua_Client::add_output_line(QString line, bool reset) {
	if (this->output == "" || reset) {
		this->output = line;
	} else {
		this->output += " .. " + Lua_Client::Newline + "  .. " + line;
	}
}

QString Lua_Client::eval() {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->expr_init(this->output);
	}
	return this->lua_vm->expr_exec(this->lua_cookie);
}

QString Lua_Client::eval(QHash<QString, QString> global_dict) {
	this->lua_vm->push_variables(global_dict);
	return this->eval();
}
