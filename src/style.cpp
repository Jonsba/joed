#include "style.h"
#include "abstract_loadable_tree.h"
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
	if (key == Keys[Name_E]) {
		this->the_name = value;
	} else if (key == Keys[Type_E]) {
		if (value == Abstract_Block::Layout_Block_Value) {
			this->the_block_type = Layout_Block_E;
		} else if (value == Abstract_Block::Text_Block_Value) {
			this->the_block_type = Text_Block_E;
		} else {
			error("Unknown type: " + value);
		}
	} else if (key == Keys[Declare_E]) {
		this->declare += value + '\n';
	} else if (key == Keys[Output_E]) {
		if (this->output == "") {
			this->output = value;
		} else {
			this->output += " .. string.char(10) .. " + value;
		}
	}
}

void Style::assign(QString key, Style* object) {
	if (key == Keys[Child_Of_E]) {
		this->parent = object;
	} else if (key == Keys[Layout_E]) {
		this->the_layout_entries.append(new Layout_Entry(object));
	} else if (key == Keys[Inherits_E]) {
		this->base_style = object;
	} else if (key == Keys[Default_Child_Style_E]) {
		this->the_default_child_style = object;
	}
}

QString Style::name() {
	return this->the_name;
}

Block_Type Style::type() {
	return this->the_block_type;
}

Style* Style::default_child_style() {
	return this->the_default_child_style;
}

QLinkedList<Layout_Entry*> Style::layout_entries() {
	return this->the_layout_entries;
}

QString Style::compile(Global_Dict global_dict) {
	if (this->lua_cookie == LUA_NOREF) {
		this->lua_cookie = this->lua_vm->expr_init(this->output);
	}
	this->lua_vm->set_global_variables(global_dict);
	return this->lua_vm->expr_exec(this->lua_cookie);
}
