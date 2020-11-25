#ifndef STYLE_PROPERTIES_H
#define STYLE_PROPERTIES_H

#include "abstract_loadable_object.h"
#include "joed.h"
#include "styles.h"

#include <QLinkedList>
#include <QScopedPointer>
#include <QString>

class Lua_Client;
class Lua_VM;
class Layout_Entry;

// The final keyword suppresses a warning when destructing object in document_styles.cpp
// Another option would be to make the destructor virtual
class Style_Properties final : Abstract_Loadable_Object {
	friend class Document_Styles;

 public:
	Style_Properties(Lua_VM* lua_vm);
	~Style_Properties();
	QLinkedList<Layout_Entry*> layout_entries();
	Style* default_child_style();
	bool is_multiblock();
	QString translate(QHash<QString, QString> key_value);

 protected:
	void assign(QString end_key, QString value, int level, bool is_first_value_line);
	void assign(QString end_key, Style* style, bool is_first_value_line);

 private:
	QLinkedList<Layout_Entry*> the_layout_entries;
	Style* the_default_child_style = nullptr;
	QScopedPointer<Lua_Client> lua_client;
};

#endif // STYLE_PROPERTIES_H
