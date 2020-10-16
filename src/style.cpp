#include "style.h"
#include "layout_entry.h"
#include "lua_vm.h"

#include <lua.hpp>

Style::Style(QString name, Lua_VM* lua_vm) {
	this->name = name;
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
}

QString Style::Get_Name() {
	return this->name;
}

Style* Style::Default_Child_Style() {
	return this->default_child_style;
}

Type_Enum Style::Get_Type() {
	return this->type;
}

Layout_Entry* Style::First_Layout_Entry() {
	return this->first_layout_entry;
}
QString Style::Compile(QString key, QString value) {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->Expr_Init(this->output);
	}
	this->lua_vm->Set_Global_Variable(key, value);
	return this->lua_vm->Expr_Exec(this->lua_cookie);
}
