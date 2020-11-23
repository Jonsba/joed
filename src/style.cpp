#include "style.h"
#include "abstract_loadable_tree.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_client.h"

Style::Style(QString name, Lua_VM* lua_vm) {
	this->the_name = name;
	this->lua_client.reset(new Lua_Client(lua_vm));
}

void Style::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	if (end_key == Field::Key::Type) {
		QStringList type_variant_pair = value.split('>');
		if (type_variant_pair[0] == Field::Value::Layout_Block) {
			this->block_type.base = Block_Base_Type::Layout_Block_E;
		} else if (type_variant_pair[0] == Field::Value::Text_Block) {
			this->block_type.base = Block_Base_Type::Text_Block_E;
			if (type_variant_pair.length() == 2) {
				if (type_variant_pair[1] == Field::Value::Title) {
					this->block_type.variant = Block_Variant::Title_E;
				}
			}
		} else {
			throw Invalid_Value_Exception();
		}
	} else if (end_key == Field::Key::Output) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	} else {
		throw Invalid_Key_Exception();
	}
}

void Style::assign(QString end_key, Style* object, bool is_first_value_line) {
	if (end_key == Field::Key::Layout) {
		if (is_first_value_line) {
			this->the_layout_entries.clear();
		}
		this->the_layout_entries.append(new Layout_Entry(object));
	} else if (end_key == Field::Key::Default_Child_Style) {
		this->the_default_child_style = object;
	} else {
		throw Invalid_Key_Exception();
	}
}

QString Style::name() { return this->the_name; }

Block_Type Style::type() { return this->block_type; }

Style* Style::default_child_style() { return this->the_default_child_style; }

QLinkedList<Layout_Entry*> Style::layout_entries() { return this->the_layout_entries; }

QString Style::translate(QHash<QString, QString> global_dict) {
	return this->lua_client->eval_expr(global_dict);
}

Style::~Style() {
	for (Layout_Entry* layout_entry : this->the_layout_entries) {
		delete layout_entry;
	}
}
