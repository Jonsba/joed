#include "style.h"
#include "abstract_loadable_tree.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_client.h"

Style::Style(QString name, Lua_VM* lua_vm) {
	this->the_name = name;
	this->lua_client.reset(new Lua_Client(lua_vm));
}

void Style::assign(QString key, QString value, bool is_first_value_line) {
	if (key == Joed::Keys[Name_E]) {
		this->the_name = value;
	} else if (key == Joed::Keys[Type_E]) {
		QStringList type_variant_pair = value.split('>');
		if (type_variant_pair[0] == Abstract_Block::Layout_Block_Value) {
			this->block_type.base = Block_Base_Type::Layout_Block_E;
		} else if (type_variant_pair[0] == Abstract_Block::Text_Block_Value) {
			this->block_type.base = Block_Base_Type::Text_Block_E;
			if (type_variant_pair.length() == 2) {
				if (type_variant_pair[1] == Abstract_Block::Title_Value) {
					this->block_type.variant = Block_Variant::Title_E;
				}
			}
		} else {
			error("Unknown type: " + value);
		}
	} else if (key == Joed::Keys[Declare_E]) {
		this->declare += value + '\n';
	} else if (key == Joed::Keys[Output_E]) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	}
}

void Style::assign(QString key, Style* object, bool is_first_value_line) {
	if (key == Joed::Keys[Child_Of_E]) {
		this->parent = object;
	} else if (key == Joed::Keys[Layout_E]) {
		if (is_first_value_line) {
			this->the_layout_entries.clear();
		}
		this->the_layout_entries.append(new Layout_Entry(object));
	} else if (key == Joed::Keys[Inherits_E]) {
		this->base_style = object;
	} else if (key == Joed::Keys[Default_Child_Style_E]) {
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
	return this->lua_client->eval_expr(global_dict);
}

Style::~Style() {
	for (Layout_Entry* layout_entry : this->the_layout_entries) {
		delete layout_entry;
	}
}
