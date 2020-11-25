#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include "exceptions.h"
#include "field.h"

enum class State { Parsing_Version, Parsing_Key, Parsing_End_Key, Parsing_Value };

class Abstract_Loadable_Object {
 public:
	// Although Definitions_Loader also derivates from Abstract_Loadable_Object,
	// the C++ standard doesn't allow it to access the protected methods of its internal
	// Abstract_Loadable_Object objects, unless we define it as a friend class
	friend class Class_File;

 protected:
	virtual void assign(QString end_key, QString value, int level, bool is_first_value_line) = 0;
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
