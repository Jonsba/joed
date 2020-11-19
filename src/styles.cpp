#include "styles.h"
#include "layout_entry.h"
#include "style.h"

Styles::Styles(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
}

void Styles::process_key(QString key, int level) {
	if (level == 1) {
		this->style_name_prefix = "";
		if (key == Field::Key::Document) {
			this->new_style = this->make_style_if_nil(Field::Key::Document);
			this->new_style->assign(Field::Key::Type, Field::Value::Layout_Block, true);
		} else if (key != Field::Key::Style) {
			throw Invalid_Key_Exception();
		}
	} else if (level >= 2) {
		if (key == Field::Key::Styles) {
			this->style_name_prefix += this->new_style->name() + ".";
		} else if (key != Field::Key::Style) {
			throw Invalid_Key_Exception();
		}
	}
}

void Styles::assign(QString key, QString value, bool is_first_value_line) {
	if (this->Keys_Object.contains(key)) {
		Style* style_object = nullptr;
		if (value != Field::Id::Children_Block) { // when key: layout
			style_object = this->make_style_if_nil(value);
		}
		this->new_style->assign(key, style_object, is_first_value_line);
	} else if (key == Field::Key::Name) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = make_style_if_nil(this->style_name_prefix + value);
	} else {
		this->new_style->assign(key, value, is_first_value_line);
	}
}

Style* Styles::find(QString name) {
	return this->list[name];
}

Style* Styles::make_style(QString name) {
	this->list[name] = new Style(name, this->lua_vm);
	this->list[name]->assign(Field::Key::Name, name, true);
	return this->list[name];
}

Style* Styles::make_style_if_nil(QString name) {
	if (this->list.contains(name)) {
		return this->list[name];
	} else {
		return this->make_style(name);
	}
}

Styles::~Styles() {
	for (Style* style : list) {
		delete style;
	}
}
