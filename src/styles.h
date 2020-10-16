#ifndef STYLES
#define STYLES

#include "style.h"

#include <QHash>
#include <QString>

class Lua_VM;

class Styles {

 public:
	Styles();
	void parse_style_identifier(QString name);
	Style* add_style(QString name);
	Style* add_style_if_nil(QString name);
	void add_value(QString key, QString value);
	Style* find(QString key);

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
