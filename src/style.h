#ifndef STYLE_H
#define STYLE_H

#include "lua_vm.h"

#include <QLinkedList>
#include <QString>

class Lua_VM;
class Layout_Entry;
typedef QLinkedList<Layout_Entry*> Layout_Entry_List;

enum Type_Enum { Unspecified_E, Multi_Block_E, Text_Block_E, Multiline_Text_Block_E };
const QString Children_Block_Value = "_children_block_";
const QString Text_Value = "_text_";

class Style {
	friend class Styles;

 public:
	Style(QString the_name, Lua_VM* lua_vm);
	QString name();
	Type_Enum type();
	Layout_Entry_List layout_entries();
	Style* default_child_style();
	QString compile(Global_Dict key_value);

 private:
	QString the_name;
	Type_Enum the_type = Unspecified_E;
	Style* base_style = nullptr;
	QString declare;
	QString output;
	Style* parent = nullptr;
	Layout_Entry_List the_layout_entries;
	Style* the_default_child_style = nullptr;
	Lua_VM* lua_vm;
	int lua_cookie;
};

#endif // STYLE_H
