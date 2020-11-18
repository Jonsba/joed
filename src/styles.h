#ifndef STYLES_H
#define STYLES_H

#include "abstract_loadable_tree.h"
#include "lua_vm.h"

#include <QHash>
#include <QString>
#include <functional>
#include <iostream>
#include <string>

class Style;

class Styles final : public Abstract_Loadable_Tree {
 public:
	Styles(Lua_VM* lua_vm);
	~Styles();
	Style* find(QString name);
	//
	inline static const QStringList Keys_Object = {Field::Key::Child_Of, Field::Key::Layout,
	                                               Field::Key::Inherits,
	                                               Field::Key::Default_Child_Style};

 protected:
	Parse_State process_key(QString key, int level);
	Parse_State assign(QString end_key, QString value, bool is_first_value_line);

 private:
	//
	Style* make_style(QString name);
	Style* make_style_if_nil(QString name);

 private:
	QHash<QString, Style*> list;
	Style* new_style;
	QString style_name_prefix;
	Lua_VM* lua_vm;
};

#endif // STYLES_H
