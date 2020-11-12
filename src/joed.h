#ifndef JOED_H
#define JOED_H

#include <QDir>
#include <QHash>
#include <QStandardPaths>
#include <QString>

void error(QString text);
void echo(QString text);
void echo(int number);

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

class Joed {

 public:
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

	inline static const QString Sep = QDir::separator();
	inline static const QString Local_Data_Path =
	    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0] + Sep + "joed" +
	    Sep;
	inline static const QString System_Data_Path =
	    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[1] + Sep + "joed" +
	    Sep;
	inline static const QString Joed_Conf_File = System_Data_Path + "joed.conf";
	inline static const QString Default_Document_Path =
	    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0] + Sep;
	inline static const QString New_Document_Name = "new-document.jod";
};

#endif // JOED_H
