#ifndef STYLE_LIST_H
#define STYLE_LIST_H

#include <QHash>
#include <QString>

struct Style_Node {
	QString layout;
	QString output;
	Style_Node *parent = nullptr;
};

class Style_List {
 public:
	Style_List();
	void Add_Style(QString style_name);
	void Add_Value(QString key, QString value);
	Style_Node *Style(QString key);

 private:
	QHash<QString, Style_Node *> list;
	Style_Node *new_node;
};

#endif // STYLE_LIST_H
