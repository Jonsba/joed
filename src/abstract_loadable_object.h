#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include "field.h"

enum class State { Parsing_Version, Parsing_Key, Parsing_End_Key, Parsing_Value };
enum class Parse_State { Success_E, Invalid_Key_E, Invalid_Value_E };

class Abstract_Loadable_Object {
 public:
	// Although Definitions_Loader also derivates from Abstract_Loadable_Object,
	// the C++ standard doesn't allow it to access the protected methods of its internal
	// Abstract_Loadable_Object objects, unless we define it as a friend class
	friend class Definitions_File;
	Abstract_Loadable_Object();

 protected:
	virtual Parse_State assign(QString end_key, QString value, bool is_first_value_line) = 0;
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
