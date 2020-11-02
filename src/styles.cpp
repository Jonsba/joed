#include "styles.h"
#include "layout_entry.h"
#include "style.h"

Styles::Styles(Lua_VM* lua_vm) {
	this->style_name_prefix = "";
	this->lua_vm = lua_vm;
}

State Styles::process_key(QString key, int level) {
	if (level >= 2) {
		if (key == Keys[Styles_E]) {
			this->style_name_prefix += this->new_style->name() + ".";
		} else if (key != Keys[Style_E]) {
			return State::Parsing_Value;
		}
	} else if (key == Keys[Document_E]) {
		this->new_style = this->make_style(Keys[Document_E]);
		this->new_style->assign(Keys[Type_E], Abstract_Block::Layout_Block_Value);
	}
	return State::Parsing_Key;
}

void Styles::assign(QString key, QString value) {
	if (this->Keys_Object.contains(key)) {
		Style* style_object = nullptr;
		if (key == Keys[Layout_E]) {
			if (value == Abstract_Block::Children_Block_Id) {
				return;
			}
		}
		style_object = this->make_style_if_nil(value);
		this->new_style->assign(key, style_object);
	} else if (key == Keys[Name_E]) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = make_style_if_nil(this->style_name_prefix + value);
	} else {
		this->new_style->assign(key, value);
	}
}

Style* Styles::find(QString name) {
	return this->list[name];
}

Style* Styles::make_style(QString name) {
	Style* style = new Style(name, this->lua_vm);
	style->assign(Keys[Name_E], name);
	this->list[name] = style;
	return style;
}

Style* Styles::make_style_if_nil(QString name) {
	if (this->list.contains(name)) {
		return this->list[name];
	} else {
		return this->make_style(name);
	}
}
