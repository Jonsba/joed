#include "styles.h"
#include "layout_entry.h"
#include "style.h"

Styles::Styles() {
	this->lua_vm = new Lua_VM();
}

State Styles::process_key(QString key, int level) {
	if (level == 2) {
		return Parsing_Value;
	}
	if (key == Keys[Document_E]) {
		this->new_style = this->add_style(Keys[Document_E]);
		this->new_style->assign(Keys[Type_E], Abstract_Block::Layout_Block_Value);
	}
	return Parsing_Key;
}

void Styles::assign(QString key, QString value) {
	if (this->Keys_Object.contains(key)) {
		Style* style_object = nullptr;
		if (key != Keys[Layout_E] || value != Abstract_Block::Children_Block_Id) {
			style_object = this->add_style_if_nil(value);
		}
		this->new_style->assign(key, style_object);
	} else if (key == Keys[Name_E]) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = add_style_if_nil(value);
	} else {
		this->new_style->assign(key, value);
	}
}

Style* Styles::find(QString key) {
	return this->list[key];
}

Style* Styles::add_style(QString name) {
	Style* style = new Style(name, this->lua_vm);
	style->assign(Keys[Name_E], name);
	this->list[name] = style;
	return style;
}

Style* Styles::add_style_if_nil(QString name) {
	if (this->list.contains(name)) {
		return this->list[name];
	} else {
		return this->add_style(name);
	}
}
