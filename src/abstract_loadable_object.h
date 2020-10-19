#ifndef PARSED_OBJECT_H
#define PARSED_OBJECT_H

#include <QString>

class Abstract_Loadable_Object {
 public:
	Abstract_Loadable_Object();
	virtual void process_intermediate_key(QString key) = 0;
	virtual void assign(QString end_key, QString value) = 0;
};

#endif // PARSED_OBJECT_H
