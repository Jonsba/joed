#include "style_properties.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_client.h"

Style_Properties::Style_Properties(Lua_VM* lua_vm) {
	this->lua_client.reset(new Lua_Client(lua_vm));
}

void Style_Properties::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	if (end_key == Field::Key::Output) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	} else {
		throw Exceptions::Invalid_Key();
	}
}

void Style_Properties::assign(QString end_key, Style* style, bool is_first_value_line) {
	if (end_key == Field::Key::Layout) {
		if (is_first_value_line) {
			this->the_layout_entries.clear();
		}
		this->the_layout_entries.append(new Layout_Entry(style));
	} else if (end_key == Field::Key::Default_Child_Style) {
		this->the_default_child_style = style;
	} else {
		throw Exceptions::Invalid_Key();
	}
}

Style* Style_Properties::default_child_style() {
	return this->the_default_child_style;
}

QLinkedList<Layout_Entry*> Style_Properties::layout_entries() {
	return this->the_layout_entries;
}

QString Style_Properties::translate(QHash<QString, QString> global_dict) {
	return this->lua_client->eval_expr(global_dict);
}

Style_Properties::~Style_Properties() {
	for (Layout_Entry* layout_entry : this->the_layout_entries) {
		delete layout_entry;
	}
}
