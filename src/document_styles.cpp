#include "document_styles.h"
#include "layout_entry.h"
#include "style.h"

Document_Styles::Document_Styles(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
	this->styles_hierarchy[0] = this->make_style_if_nil(Field::Key::Document);
	this->styles_hierarchy[0]->assign(Field::Key::Type, Field::Value::Layout_Block, true);
}

void Document_Styles::process_key(QString key, int level) {
	int style_level = level / 2;
	if (key == Field::Key::Properties || key == Field::Key::Styles) {
		this->current_style = this->styles_hierarchy[style_level];
	} else {
		// A style declaration can only have a level of {0, 2, 4, 6, ...}
		if (level % 2 == 1) {
			throw Invalid_Key_Exception();
		}
		// The style may be already created (e.g. it was referenced by a default-child-style entry)
		this->current_style = this->make_style_if_nil(prefix_style_name(key, style_level));
		this->styles_hierarchy[style_level] = current_style;
	}
}

void Document_Styles::assign(QString key, QString value, bool is_first_value_line) {
	if (this->Keys_Object.contains(key)) {
		Style* style_object = nullptr;
		// Children entries in layouts have no style
		if (value != Field::Id::Children_Block) {
			style_object = this->make_style_if_nil(value);
		}
		this->current_style->assign(key, style_object, is_first_value_line);
	} else {
		this->current_style->assign(key, value, is_first_value_line);
	}
}

Style* Document_Styles::find(QString name) {
	return this->list[name];
}

Style* Document_Styles::make_style(QString name) {
	this->list[name] = new Style(name, this->lua_vm);
	return this->list[name];
}

Style* Document_Styles::make_style_if_nil(QString name) {
	if (this->list.contains(name)) {
		return this->list[name];
	} else {
		return this->make_style(name);
	}
}

QString Document_Styles::prefix_style_name(QString style_name, int style_level) {
	QString prefix = "";
	// Level 1 styles won't be prefixed (with 'document.')
	if (style_level > 1) {
		prefix = this->styles_hierarchy[style_level - 1]->name() + ".";
	}
	return prefix + style_name;
}

Document_Styles::~Document_Styles() {
	for (Style* style : list) {
		delete style;
	}
}
