#include "styles.h"
#include "layout_entry.h"
#include "style_properties.h"

Styles::Styles(Lua_VM* lua_vm) {
	this->lua_vm = lua_vm;
	this->Children_Style = this->make_primitive_style(Field::Id::Children, Style_Type::Children_E);
	this->Raw_Text_Style = this->make_primitive_style(Field::Id::Text, Style_Type::Raw_Text_E);
	this->styles_hierarchy[0] = this->make_style_if_nil(Field::Key::Document);
	this->styles_hierarchy[0]->type = Style_Type::Layouted_E;
}

void Styles::process_intermediate_key(QString key, int level) {
	if (key == Field::Key::Styles) {
		return;
	}
	// A style declaration can only have a level of {0, 2, 4, 6, ...}
	if (level % 2 == 1) {
		throw Exceptions::Invalid_Key();
	}
	// The style may be already created (e.g. it was referenced by a default-child-style entry)
	this->styles_hierarchy[level / 2] = this->make_style_if_nil(prefix_style_name(key, level / 2));
}

void Styles::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	current_style = this->styles_hierarchy[level / 2];
	if (this->Keys_Object.contains(end_key)) {
		this->current_style->properties->assign(end_key, this->make_style_if_nil(value),
		                                        is_first_value_line);
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
				throw Exceptions::Invalid_Value();
			}
		} else {
			this->current_style->properties->assign(end_key, value, level, is_first_value_line);
		}
	}
}

Style* Styles::find(QString name) {
	return this->styles[name];
}

Style* Styles::make_primitive_style(QString id, Style_Type type) {
	this->styles[id] = new Style({id, type, Style_Variant::Standard_E, nullptr});
	return this->styles[id];
}

Style* Styles::make_style(QString name) {
	this->styles[name] = new Style();
	this->styles[name]->identifier = name;
	this->styles[name]->properties = new Style_Properties(this->lua_vm);
	return this->styles[name];
}

Style* Styles::make_style_if_nil(QString name) {
	if (this->styles.contains(name)) {
		return this->styles[name];
	} else {
		return this->make_style(name);
	}
}

QString Styles::prefix_style_name(QString style_name, int style_level) {
	QString prefix = "";
	// Level 1 styles won't be prefixed (with 'document.')
	if (style_level > 1) {
		prefix = this->styles_hierarchy[style_level - 1]->identifier + ".";
	}
	return prefix + style_name;
}

Styles::~Styles() {
	for (Style* style : styles) {
		delete style;
	}
}
