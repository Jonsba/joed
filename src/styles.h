#ifndef STYLES_H
#define STYLES_H

#include "abstract_loadable_object.h"

#include <QHash>
#include <QString>

class Lua_VM;
class Style;

class Styles : public Abstract_Loadable_Object {
 public:
	Styles();
	virtual State process_intermediate_key(QString key, int level);
	virtual void assign(QString end_key, QString value);
	Style* find(QString key);

 private:
	//
	Style* add_style(QString name);
	Style* add_style_if_nil(QString name);

 private:
	QHash<QString, Style*> list;
	Style* new_style;
	Lua_VM* lua_vm;
};

#endif // STYLES_H
