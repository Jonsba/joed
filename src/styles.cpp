#include "styles.h"
#include "layout_entry.h"
#include "style.h"

Styles::Styles(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
}

void Styles::process_key(QString key, int level) {
	if (level == 1) {
		this->style_name_prefix = "";
		if (key == Joed::Keys[Document_E]) {
			this->new_style = this->make_style_if_nil(Joed::Keys[Document_E]);
			this->new_style->assign(Joed::Keys[Type_E], Abstract_Block::Layout_Block_Value, true);
		}
	} else if (level >= 2) {
		if (key == Joed::Keys[Styles_E]) {
			this->style_name_prefix += this->new_style->name() + ".";
		}
	}
}

void Styles::assign(QString key, QString value, bool is_first_value_line) {
	if (this->Keys_Object.contains(key)) {
		Style* style_object = nullptr;
		if (value != Abstract_Block::Children_Block_Id) { // when key: layout
			style_object = this->make_style_if_nil(value);
		}
		this->new_style->assign(key, style_object, is_first_value_line);
	} else if (key == Joed::Keys[Name_E]) {
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
	this->list[name]->assign(Joed::Keys[Name_E], name, true);
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
