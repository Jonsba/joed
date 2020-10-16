#include "styles.h"
#include "joed.h"
#include "layout_entry.h"
#include "lua_vm.h"

Styles::Styles() {
	this->lua_vm = new Lua_VM();
}

// name: document or new-style
void Styles::parse_style_identifier(QString name) {
	if (name == Joed::Document_Key) {
		this->new_style = this->add_style(name);
		this->new_style->the_type = Multi_Block_E;
		this->new_style->style_name = name;
	} else if (name != Joed::New_Style_Key) {
		print(name + " is an unknown style");
		throw;
	}
	last_layout_entry = nullptr;
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

void Styles::add_value(QString key, QString value) {
	if (key == Joed::Name_Key) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = add_style_if_nil(value);
	} else if (key == Joed::Type_Key) {
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
	} else if (key == Joed::Child_Of_Key) {
		this->new_style->parent = this->list[value];
	} else if (key == Joed::Layout_Key) {
		Layout_Entry* layout_entry = new Layout_Entry();
		// last_layout_entry = layout_entry;
		if (last_layout_entry == nullptr) {
			this->new_style->the_first_layout_entry = layout_entry;
			last_layout_entry = layout_entry;
		} else {
			last_layout_entry->next = layout_entry;
			last_layout_entry = last_layout_entry->next;
		}
		layout_entry->the_style = this->add_style_if_nil(value);
	} else if (key == Joed::Declare_Key) {
		this->new_style->declare += value + '\n';
	} else if (key == Joed::Output_Key) {
		if (this->new_style->output == "") {
			this->new_style->output = value;
		} else {
			this->new_style->output += " .. string.char(10) .. " + value;
		}
	} else if (key == Joed::Inherits_Key) {
		Style* base_style = this->add_style_if_nil(value);
		this->new_style->base_style = base_style;
	} else if (key == Joed::Default_Child_Style_Key) {
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
