#include "style_list.h"
#include "joed.h"

Style_List::Style_List() {}

void Style_List::Add_Style(QString style_name) {
	this->new_node = new Style_Node();
	if (style_name == Joed::Document_Key) {
		this->list[style_name] = this->new_node;
	} else if (style_name != Joed::New_Style_Key) {
		print(style_name + " is an unknown style");
		throw;
	}
}

void Style_List::Add_Value(QString key, QString value) {
	if (key == Joed::Name_Key) {
		this->list[value] = this->new_node;
	} else if (key == Joed::Child_Of_Key) {
		this->new_node->parent = this->list[value];
	} else if (key == Joed::Layout_Key) {
		this->new_node->layout += value + '\n';
	} else if (key == Joed::Output_Key) {
		this->new_node->output += value + '\n';
	} else {
		print(key + " is an unknown key");
		throw;
	}
}

Style_Node *Style_List::Style(QString key) {
	return this->list[key];
}
