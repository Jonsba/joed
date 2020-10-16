#include "styles.h"
#include "layout_entry.h"

Styles::Styles() {
	this->lua_vm = new Lua_VM();
}

void Styles::process_intermediate_key(QString key) {
	if (key == Style::Document_Key) {
		this->new_style = this->add_style(Style::Document_Key);
		this->new_style->the_type = Multi_Block_E;
		this->new_style->the_name = Style::Document_Key;
	} else if (key != Style::New_Style_Key) {
		print(key + " is an unknown style");
		throw;
	}
}

void Styles::assign(QString key, QString value) {
	if (key == Style::Name_Key) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = add_style_if_nil(value);
	} else if (key == Style::Type_Key) {
		if (value == Multi_Block_Value) {
			this->new_style->the_type = Multi_Block_E;
		} else if (value == Text_Block_Value) {
			this->new_style->the_type = Text_Block_E;
		} else if (value == Multiline_Text_Block_Value) {
			this->new_style->the_type = Multiline_Text_Block_E;
		} else {
			print("Unknown type: " + value);
			throw;
		}
	} else if (key == Style::Child_Of_Key) {
		this->new_style->parent = this->list[value];
	} else if (key == Style::Layout_Key) {
		Layout_Entry* layout_entry = new Layout_Entry(this->add_style_if_nil(value));
		new_style->the_layout_entries.append(layout_entry);
	} else if (key == Style::Declare_Key) {
		this->new_style->declare += value + '\n';
	} else if (key == Style::Output_Key) {
		if (this->new_style->output == "") {
			this->new_style->output = value;
		} else {
			this->new_style->output += " .. string.char(10) .. " + value;
		}
	} else if (key == Style::Inherits_Key) {
		Style* base_style = this->add_style_if_nil(value);
		this->new_style->base_style = base_style;
	} else if (key == Style::Default_Child_Style_Key) {
		Style* default_child_style = this->add_style_if_nil(value);
		this->new_style->the_default_child_style = default_child_style;
	} else {
		print(key + " is an unknown key");
		throw;
	}
}

Style* Styles::find(QString key) {
	return this->list[key];
}

Style* Styles::add_style(QString name) {
	Style* style = new Style(name, this->lua_vm);
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
