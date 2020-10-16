#include "style.h"
#include "layout_entry.h"
#include "lua_vm.h"

#include <lua.hpp>

Style::Style(QString name, Lua_VM* lua_vm) {
	this->style_name = name;
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
}

QString Style::name() {
	return this->style_name;
}

Style* Style::default_child_style() {
	return this->the_default_child_style;
}

Type_Enum Style::type() {
	return this->the_type;
}

Layout_Entry* Style::first_layout_entry() {
	return this->the_first_layout_entry;
}
QString Style::compile(QString key, QString value) {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->expr_init(this->output);
	}
	this->lua_vm->set_global_variable(key, value);
	return this->lua_vm->expr_exec(this->lua_cookie);
}
