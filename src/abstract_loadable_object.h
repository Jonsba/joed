#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include "joed.h"

enum class State { Starting, Parsing_Key, Parsing_Value };

class Abstract_Loadable_Object {
 public:
	Abstract_Loadable_Object();

 protected:
	virtual void assign(QString end_key, QString value, bool is_first_value_line) = 0;
	//
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
