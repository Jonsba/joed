#include "styles.h"
#include "joed.h"
#include "layout_entry.h"

Styles::Styles() {}

// name: document or new-style
void Styles::Parse_Style_Identifier(QString name) {
	if (name == Joed::Document_Key) {
		this->new_style = this->Add_Style(name);
		this->new_style->type = Multi_Block_E;
		this->new_style->name = name;
	} else if (name != Joed::New_Style_Key) {
		print(name + " is an unknown style");
		throw;
	}
	last_layout_entry = nullptr;
}

Style* Styles::Add_Style(QString name) {
	Style* style = new Style(name);
	this->list[name] = style;
	return style;
}

Style* Styles::Add_Style_If_Nil(QString name) {
	Style* style = this->list[name];
	if (style == nullptr) {
		style = this->Add_Style(name);
	}
	return style;
}

void Styles::Add_Value(QString key, QString value) {
	if (key == Joed::Name_Key) {
		// Style may be already created (e.g. it was referenced by a default-child-style entry)
		this->new_style = Add_Style_If_Nil(value);
	} else if (key == Joed::Type_Key) {
		if (value == Multi_Block_Value) {
			this->new_style->type = Multi_Block_E;
		} else if (value == Text_Block_Value) {
			this->new_style->type = Text_Block_E;
		} else if (value == Multiline_Text_Block_Value) {
			this->new_style->type = Multiline_Text_Block_E;
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
			this->new_style->first_layout_entry = layout_entry;
			last_layout_entry = layout_entry;
		} else {
			last_layout_entry->next = layout_entry;
			last_layout_entry = last_layout_entry->next;
		}
		layout_entry->style = this->Add_Style_If_Nil(value);
	} else if (key == Joed::Declare_Key) {
		this->new_style->declare += value + '\n';
	} else if (key == Joed::Output_Key) {
		this->new_style->output += value + '\n';
	} else if (key == Joed::Inherits_Key) {
		Style* base_style = this->Add_Style_If_Nil(value);
		this->new_style->base_style = base_style;
	} else if (key == Joed::Default_Child_Style_Key) {
		Style* default_child_style = this->Add_Style_If_Nil(value);
		this->new_style->default_child_style = default_child_style;
	} else {
		print(key + " is an unknown key");
		throw;
	}
}

Style* Styles::Find(QString key) {
	return this->list[key];
}
