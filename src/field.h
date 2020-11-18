#ifndef FIELD_H
#define FIELD_H

#include <QStringList>

enum Key_Index {
	Version_E = 0,
	Backend_E,
	Styles_E,
	Name_E,
	Doc_File_Ext_E,
	Env_File_Ext_E,
	Viewer_E,
	Escape_Table_E,
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
	Default_Child_Style_E,
	Environment_E
};

struct Field {

	inline static const QStringList Keys = {"format-version",
	                                        "backend",
	                                        "styles",
	                                        "name",
	                                        "doc-file-ext",
	                                        "env-file-ext",
	                                        "viewer",
	                                        "escape-table",
	                                        "document-class",
	                                        "content",
	                                        "children",
	                                        "block",
	                                        "text",
	                                        "style",
	                                        "defaults",
	                                        "document",
	                                        "child-of",
	                                        "type",
	                                        "layout",
	                                        "declare",
	                                        "output",
	                                        "inherits",
	                                        "default-child-style",
	                                        "environment"};
};

#endif // FIELD_H
