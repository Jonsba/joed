#include "style.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_vm.h"

#include <lua.hpp>

Style::Style(QString name, Lua_VM* lua_vm) {
	this->the_name = name;
	this->lua_vm = lua_vm;
	this->lua_cookie = LUA_NOREF;
}

void Style::assign(QString key, QString value) {
	if (key == Style::Name_Key) {
		this->the_name = value;
	} else if (key == Style::Type_Key) {
		if (value == Multi_Block_Value) {
			this->the_type = Multi_Block_E;
		} else if (value == Text_Block_Value) {
			this->the_type = Text_Block_E;
		} else if (value == Multiline_Text_Block_Value) {
			this->the_type = Multiline_Text_Block_E;
		} else {
			error("Unknown type: " + value);
		}
	} else if (key == Style::Declare_Key) {
		this->declare += value + '\n';
	} else if (key == Style::Output_Key) {
		if (this->output == "") {
			this->output = value;
		} else {
			this->output += " .. string.char(10) .. " + value;
		}
	} else {
		error(key + " is an unknown key");
	}
}

void Style::set_parent(Style* parent) {
	this->parent = parent;
}
void Style::set_base_style(Style* base_style) {
	this->base_style = base_style;
}
void Style::set_default_child_style(Style* the_default_child_style) {
	this->the_default_child_style = the_default_child_style;
}
void Style::append_layout_entry(Layout_Entry* layout_entry) {
	this->the_layout_entries.append(layout_entry);
}

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
