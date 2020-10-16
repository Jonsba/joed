#ifndef STYLES_H
#define STYLES_H

#include "abstract_buildable_object.h"
#include "style.h"

#include <QHash>
#include <QString>

class Lua_VM;

class Styles : public Abstract_Buildable_Object {
 public:
	Styles();
	virtual void process_intermediate_key(QString key);
	virtual void assign(QString end_key, QString value);
	Style* find(QString key);

 private:
	const QString Multi_Block_Value = "multi_block";
	const QString Text_Block_Value = "text_block";
	const QString Multiline_Text_Block_Value = "multiline_text_block";
	//
	Style* add_style(QString name);
	Style* add_style_if_nil(QString name);

 private:
	QHash<QString, Style*> list;
	Style* new_style;
	Lua_VM* lua_vm;
};

#endif // STYLES_H
