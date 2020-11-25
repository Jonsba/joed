#include "document_styles.h"
#include "layout_entry.h"
#include "style_properties.h"

Document_Styles::Document_Styles(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
	this->styles_hierarchy[0] = this->make_style_if_nil(Field::Key::Document);
	this->styles_hierarchy[0]->type = Style_Type::Layouted_E;
}

void Document_Styles::process_intermediate_key(QString key, int level) {
	if (key == Field::Key::Styles) {
		return;
	}
	// A style declaration can only have a level of {0, 2, 4, 6, ...}
	if (level % 2 == 1) {
		throw Invalid_Key_Exception();
	}
	// The style may be already created (e.g. it was referenced by a default-child-style entry)
	this->styles_hierarchy[level / 2] = this->make_style_if_nil(prefix_style_name(key, level / 2));
}

void Document_Styles::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	current_style = this->styles_hierarchy[level / 2];
	if (this->Keys_Object.contains(end_key)) {
		Style* style_object = Raw_Styles::Children_Style;
		if (value != Field::Id::Children_Block) {
			style_object = this->make_style_if_nil(value);
		}
		this->current_style->properties->assign(end_key, style_object, is_first_value_line);
	} else {
		if (end_key == Field::Key::Type) {
			QStringList type_variant_pair = value.split('>');
			if (type_variant_pair[0] == Field::Value::Layout_Block) {
				this->current_style->type = Style_Type::Layouted_E;
			} else if (type_variant_pair[0] == Field::Value::Text_Block) {
				this->current_style->type = Style_Type::Text_E;
				if (type_variant_pair.length() == 2) {
					if (type_variant_pair[1] == Field::Value::Title) {
						this->current_style->variant = Style_Variant::Title_E;
					}
				}
			} else {
				throw Invalid_Value_Exception();
			}
		} else {
			this->current_style->properties->assign(end_key, value, level, is_first_value_line);
		}
	}
}

Style* Document_Styles::find(QString name) {
	return this->list[name];
}

Style* Document_Styles::make_style(QString name) {
	this->list[name] = new Style();
	this->list[name]->identifier = name;
	this->list[name]->properties = new Style_Properties(this->lua_vm);
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
		prefix = this->styles_hierarchy[style_level - 1]->identifier + ".";
	}
	return prefix + style_name;
}

Document_Styles::~Document_Styles() {
	for (Style* style : list) {
		delete style;
	}
}
