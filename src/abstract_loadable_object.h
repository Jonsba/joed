#ifndef ABSTRACT_LOADABLE_OBJECT_H
#define ABSTRACT_LOADABLE_OBJECT_H

#include <QStringList>

enum class State { Starting, Parsing_Key, Parsing_Value };

class Abstract_Loadable_Object {
 public:
	Abstract_Loadable_Object();
	virtual void assign(QString end_key, QString value) = 0;
	//
	enum Key_Index {
		Version_E = 0,
		Backend_E,
		Styles_E,
		Name_E,
		File_Extension_E,
		Exec_E,
		Document_Class_E,
		Content_E,
		Children_E,
		Block_E,
		Text_E,
		Style_E,
		Defaults_E,
		Document_E,
		Child_Of_E,
		Type_E,
		Layout_E,
		Declare_E,
		Output_E,
		Inherits_E,
		Default_Child_Style_E
	};
	inline static const QStringList Keys = {
	    "format-version", "backend",        "styles",
	    "name",           "file-extension", "exec",
	    "document-class", "content",        "children",
	    "block",          "text",           "style",
	    "defaults",       "document",       "child-of",
	    "type",           "layout",         "declare",
	    "output",         "inherits",       "default-child-style"};
};

#endif // ABSTRACT_LOADABLE_OBJECT_H
