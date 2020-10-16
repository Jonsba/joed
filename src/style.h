#ifndef STYLE_H
#define STYLE_H

#include "joed.h"
#include "lua_vm.h"

#include <QLinkedList>
#include <QString>
#include <QVector>

class Lua_VM;
class Layout_Entry;
typedef QLinkedList<Layout_Entry*> Layout_Entry_List;

enum Type_Enum { Unspecified_E, Multi_Block_E, Text_Block_E, Multiline_Text_Block_E };

class Style {
	friend class Styles;

 public:
	Style(QString the_name, Lua_VM* lua_vm);
	void assign(QString key, QString value);
	QString name();
	Type_Enum type();
	Layout_Entry_List layout_entries();
	Style* default_child_style();
	QString compile(Global_Dict key_value);
	//
	inline static const QString Document_Key = "document";
	inline static const QString New_Style_Key = "new-style";
	inline static const QString Name_Key = "name";
	inline static const QString Child_Of_Key = "child-of";
	inline static const QString Type_Key = "type";
	inline static const QString Layout_Key = "layout";
	inline static const QString Declare_Key = "declare";
	inline static const QString Output_Key = "output";
	inline static const QString Inherits_Key = "inherits";
	inline static const QString Default_Child_Style_Key = "default-child-style";
	inline static const QString_Vector Intermediate_Keys = {Document_Key, New_Style_Key};
	inline static const QString_Vector End_Keys = {
	    Name_Key,    Child_Of_Key, Type_Key,     Layout_Key,
	    Declare_Key, Output_Key,   Inherits_Key, Default_Child_Style_Key};
	inline static const QString Children_Block_Value = "_children_block_";
	inline static const QString Text_Value = "_text_";

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
