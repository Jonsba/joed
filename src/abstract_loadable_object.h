#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include <QStringList>

enum State { Starting, Parsing_Key, Parsing_Value };

class Abstract_Loadable_Object {
 public:
	Abstract_Loadable_Object();
	virtual void assign(QString end_key, QString value) = 0;
	//
	enum Key_Index {
		Version_E = 0,
		Backend_E = 1,
		Styles_E = 2,
		Name_E = 3,
		Exec_E = 4,
		Document_Class_E = 5,
		Content_E = 6,
		Children_E = 7,
		Block_E = 8,
		Text_E = 9,
		Style_E = 10,
		Defaults_E = 11,
		Document_E = 12,
		Child_Of_E = 13,
		Type_E = 14,
		Layout_E = 15,
		Declare_E = 16,
		Output_E = 17,
		Inherits_E = 18,
		Default_Child_Style_E = 19
	};
	inline static const QStringList Keys = {
	    "version",  "backend", "styles",  "name",   "exec",     "document-class",     "content",
	    "children", "block",   "text",    "style",  "defaults", "document",           "child-of",
	    "type",     "layout",  "declare", "output", "inherits", "default-child-style"};
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
