#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include <QString>
#include <QStringList>

enum State { Starting, Parsing_Key, Parsing_Value };

class Abstract_Loadable_Object {
 public:
	Abstract_Loadable_Object(QStringList keys_objects = {});

	virtual State process_intermediate_key(QString key, int level) = 0;
	virtual void assign(QString end_key, QString value) = 0;

	bool is_key_object(QString end_key);

 private:
	QStringList keys_style_values;
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
