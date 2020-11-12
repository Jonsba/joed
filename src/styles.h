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

class Styles : public Abstract_Loadable_Tree {
 public:
	Styles(Lua_VM* lua_vm);
	~Styles();
	State process_key(QString key, int level);

	void assign(QString end_key, QString value, bool is_first_value_line);

	Style* find(QString name);
	//
	inline static const QStringList Keys_Object = {Joed::Keys[Child_Of_E], Joed::Keys[Layout_E],
	                                               Joed::Keys[Inherits_E],
	                                               Joed::Keys[Default_Child_Style_E]};

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
