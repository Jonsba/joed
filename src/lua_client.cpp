#include "lua_client.h"
#include "lua_vm.h"
#include <lua.hpp>

Lua_Client::Lua_Client(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
	this->expr = "";
}

void Lua_Client::add_expr_line(QString line, bool reset) {
	if (this->expr == "" || reset) {
		this->expr = line;
	} else {
		this->expr += " .. " + Lua_Client::Newline + "  .. " + line;
	}
}

QString Lua_Client::eval_expr() {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->load_expr(this->expr);
	}
	return this->lua_vm->eval_expr(this->lua_cookie);
}

QString Lua_Client::eval_expr(QHash<QString, QString> global_dict) {
	this->lua_vm->push_variables(global_dict);
	return this->eval_expr();
}

QStringList Lua_Client::eval_inline_array_expr(QString array_expr, int array_size) {
	QStringList ret;
	luaL_dostring(this->lua_vm->L(), to_chars("return " + array_expr));
	for (int i = 1; i <= array_size; i++) {
		lua_pushinteger(this->lua_vm->L(), i);
		lua_gettable(this->lua_vm->L(), -2);
		ret.append(QString(lua_tostring(this->lua_vm->L(), -1)));
		lua_pop(this->lua_vm->L(), 1);
	}
	lua_pop(this->lua_vm->L(), 1);
	return ret;
}
