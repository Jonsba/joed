#include "style.h"
#include "abstract_loadable_tree.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_client.h"

Style::Style(QString name, Lua_VM* lua_vm) {
	this->the_name = name;
	this->lua_client = new Lua_Client(lua_vm);
}

void Style::assign(QString key, QString value) {
	if (key == Keys[Name_E]) {
		this->the_name = value;
	} else if (key == Keys[Type_E]) {
		if (value == Abstract_Block::Layout_Block_Value) {
			this->block_type = Block_Type::Layout_Block_E;
		} else if (value == Abstract_Block::Text_Block_Value) {
			this->block_type = Block_Type::Text_Block_E;
		} else {
			error("Unknown type: " + value);
		}
	} else if (key == Keys[Declare_E]) {
		this->declare += value + '\n';
	} else if (key == Keys[Output_E]) {
		if (this->output == "") {
			this->output = value;
		} else {
			this->output += " .. " + Lua_Client::Newline + "  .. " + value;
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
	return this->block_type;
}

Style* Style::default_child_style() {
	return this->the_default_child_style;
}

QLinkedList<Layout_Entry*> Style::layout_entries() {
	return this->the_layout_entries;
}

QString Style::translate(QHash<QString, QString> global_dict) {
	return this->lua_client->eval(this->output, global_dict);
}
