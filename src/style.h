#ifndef STYLE_H
#define STYLE_H

#include <QString>

class Layout_Entry;

enum Type_Enum { Unspecified_E, Multi_Block_E, Text_Block_E, Multiline_Text_Block_E };
const QString Children_Block_Value = "_children_block_";

class Style {
	friend class Styles;

 public:
	Style(QString name);
	QString Get_Name();
	Type_Enum Get_Type();
	Layout_Entry* First_Layout_Entry();
	Style* Default_Child_Style();

 private:
	QString name;
	Type_Enum type = Unspecified_E;
	Style* base_style = nullptr;
	QString declare;
	QString output;
	Style* parent = nullptr;
	Layout_Entry* first_layout_entry = nullptr;
	Style* default_child_style = nullptr;
};

#endif // STYLE_H
