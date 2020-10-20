#include "styles.h"
#include "layout_entry.h"
#include "style.h"

Styles::Styles() {
	this->lua_vm = new Lua_VM();
}

State Styles::process_intermediate_key(QString key, int level) {
	if (level == 2) {
		return Parsing_Value;
	}
	if (level == 1) {
		// N level is 2, then level == 0 is the only possibility here
		if (key == Style::Document_Key) {
			this->new_style = this->add_style(Style::Document_Key);
			this->new_style->assign(Style::Type_Key, Style::Multi_Block_Value);
		} else if (key != Style::Style_Key) {
			error(key + " is an unknown style");
		}
	}
	return Parsing_Key;
}

void Styles::assign(QString key, QString value) {
	if (key == Style::Name_Key) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = add_style_if_nil(value);
	} else if (key == Style::Child_Of_Key) {
		this->new_style->set_parent(this->list[value]);
	} else if (key == Style::Layout_Key) {
		this->new_style->append_layout_entry(new Layout_Entry(this->add_style_if_nil(value)));
	} else if (key == Style::Inherits_Key) {
		this->new_style->set_base_style(this->add_style_if_nil(value));
	} else if (key == Style::Default_Child_Style_Key) {
		this->new_style->set_default_child_style(this->add_style_if_nil(value));
	} else {
		this->new_style->assign(key, value);
	}
}

Style* Styles::find(QString key) {
	return this->list[key];
}

Style* Styles::add_style(QString name) {
	Style* style = new Style(name, this->lua_vm);
	style->assign(Style::Name_Key, name);
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
