#ifndef STYLES_H
#define STYLES_H

#include "abstract_loadable_tree.h"
#include "style.h"

#include <QHash>

class Lua_VM;

class Styles final : public Abstract_Loadable_Tree {
 public:
	Styles(Lua_VM* lua_vm);
	~Styles();
	Style* find(QString name);
	// Constants (or supposed to be)
	inline static Style* Children_Style;
	inline static Style* Raw_Text_Style;
	inline static const QStringList Keys_Object = {Field::Key::Layout,
	                                               Field::Key::Default_Child_Style};

 protected:
	void process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value, int level, bool is_first_value_line);

 private:
	Style* make_primitive_style(QString id, Style_Type type);
	Style* make_style(QString name);
	Style* make_style_if_nil(QString name);
	QString prefix_style_name(QString style_name, int level);

 private:
	QHash<QString, Style*> styles;
	Style* current_style;
	QHash<int, Style*> styles_hierarchy;
	Lua_VM* lua_vm;
};

#endif // STYLES_H
