#ifndef STYLES
#define STYLES

#include "style.h"

#include <QHash>
#include <QString>

class Lua_VM;

class Styles {

 public:
	Styles();
	void Parse_Style_Identifier(QString name);
	Style* Add_Style(QString name);
	Style* Add_Style_If_Nil(QString name);
	void Add_Value(QString key, QString value);
	void Finalize();
	Style* Find(QString key);

 private:
	const QString Multi_Block_Value = "multi_block";
	const QString Text_Block_Value = "text_block";
	const QString Multiline_Text_Block_Value = "multiline_text_block";

	QHash<QString, Style*> list;
	Style* new_style;
	Layout_Entry* last_layout_entry;
	Lua_VM* lua_vm;
};

#endif // STYLES
