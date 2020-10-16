#ifndef STYLE_H
#define STYLE_H

#include <QString>

class Lua_VM;
class Layout_Entry;

enum Type_Enum { Unspecified_E, Multi_Block_E, Text_Block_E, Multiline_Text_Block_E };
const QString Children_Block_Value = "_children_block_";
const QString Text_Value = "_text_";

class Style {
	friend class Styles;

 public:
	Style(QString name, Lua_VM* lua_vm);
	QString Get_Name();
	Type_Enum Get_Type();
	Layout_Entry* First_Layout_Entry();
	Style* Default_Child_Style();
	QString Compile(QString key, QString value);

 private:
	QString name;
	Type_Enum type = Unspecified_E;
	Style* base_style = nullptr;
	QString declare;
	QString output;
	Style* parent = nullptr;
	Layout_Entry* first_layout_entry = nullptr;
	Style* default_child_style = nullptr;
	Lua_VM* lua_vm;
	int lua_cookie;
};

#endif // STYLE_H
