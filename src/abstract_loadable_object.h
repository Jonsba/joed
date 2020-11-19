#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include "field.h"

enum class State { Parsing_Version, Parsing_Key, Parsing_End_Key, Parsing_Value };

enum class Parse_Exception_Code { Invalid_Key, Invalid_Value, Invalid_Indent, Other };
struct Parse_Exception {
	Parse_Exception_Code code;
	QString msg = "";
};

struct Invalid_Key_Exception : Parse_Exception {
	Invalid_Key_Exception() : Parse_Exception({Parse_Exception_Code::Invalid_Key, ""}) {}
};

struct Invalid_Value_Exception : Parse_Exception {
	Invalid_Value_Exception() : Parse_Exception({Parse_Exception_Code::Invalid_Value, ""}) {}
};

struct Invalid_Indent_Exception : Parse_Exception {
	Invalid_Indent_Exception() : Parse_Exception({Parse_Exception_Code::Invalid_Indent, ""}) {}
};

class Abstract_Loadable_Object {
 public:
	// Although Definitions_Loader also derivates from Abstract_Loadable_Object,
	// the C++ standard doesn't allow it to access the protected methods of its internal
	// Abstract_Loadable_Object objects, unless we define it as a friend class
	friend class Definitions_File;
	Abstract_Loadable_Object();

 protected:
	virtual void assign(QString end_key, QString value, bool is_first_value_line) = 0;
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
