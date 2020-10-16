#include "style.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_vm.h"

#include <lua.hpp>

Style::Style(QString name, Lua_VM* lua_vm) { // : Document_Key("document") {
	this->the_name = name;
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
	// this->Document_Key = "document";
}

void Style::assign(QString key, QString value) {}

QString Style::name() {
	return this->the_name;
}

Style* Style::default_child_style() {
	return this->the_default_child_style;
}

Type_Enum Style::type() {
	return this->the_type;
}

Layout_Entry_List Style::layout_entries() {
	return this->the_layout_entries;
}
QString Style::compile(Global_Dict global_dict) {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->expr_init(this->output);
	}
	this->lua_vm->set_global_variables(global_dict);
	return this->lua_vm->expr_exec(this->lua_cookie);
}
