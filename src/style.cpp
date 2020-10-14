#include "style.h"
#include "layout_entry.h"

Style::Style(QString name) {
	this->name = name;
}

QString Style::Get_Name() {
	return this->name;
}

Style* Style::Default_Child_Style() {
	return this->default_child_style;
}

// QVector<Layout_Enum> Style::Layout_List() {
//	return this->layout;
//}

Type_Enum Style::Get_Type() {
	return this->type;
}

Layout_Entry* Style::First_Layout_Entry() {
	return this->first_layout_entry;
}
