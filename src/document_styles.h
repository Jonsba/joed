#ifndef DOCUMENT_STYLES_H
#define DOCUMENT_STYLES_H

#include "abstract_loadable_tree.h"
#include "lua_vm.h"

#include <QHash>
#include <QString>
#include <functional>
#include <iostream>
#include <string>

class Style;

class Document_Styles final : public Abstract_Loadable_Tree {
 public:
	Document_Styles(Lua_VM* lua_vm);
	~Document_Styles();
	Style* find(QString name);
	//
	inline static const QStringList Keys_Object = {Field::Key::Layout,
	                                               Field::Key::Default_Child_Style};

 protected:
	void process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value, int level, bool is_first_value_line);

 private:
	//
	Style* make_style(QString name);
	Style* make_style_if_nil(QString name);
	QString prefix_style_name(QString style_name, int level);

 private:
	QHash<QString, Style*> list;
	Style* current_style;
	QHash<int, Style*> styles_hierarchy;
	Lua_VM* lua_vm;
};

#endif // DOCUMENT_STYLES_H
