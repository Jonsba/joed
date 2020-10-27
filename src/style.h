#ifndef STYLE_H
#define STYLE_H

#include "abstract_block.h"
#include "abstract_loadable_object.h"
#include "joed.h"

#include <QLinkedList>
#include <QString>

class Lua_VM;
class Lua_Client;
class Layout_Entry;

class Style : Abstract_Loadable_Object {

 public:
	Style(QString the_name, Lua_VM* lua_vm);
	void assign(QString key, QString value);
	void assign(QString key, Style* object);
	QString name();
	Block_Type type();
	QLinkedList<Layout_Entry*> layout_entries();
	Style* default_child_style();
	bool is_multiblock();
	QString compile(QHash<QString, QString> key_value);

 private:
	//
	QString the_name;
	Style* base_style = nullptr;
	QString declare;
	QString output;
	Style* parent = nullptr;
	QLinkedList<Layout_Entry*> the_layout_entries;
	Style* the_default_child_style = nullptr;
	Lua_Client* lua_client;
	Block_Type block_type;
};

#endif // STYLE_H
