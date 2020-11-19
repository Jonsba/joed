#ifndef ABSTRACT_LOADABLE_FILE_H
#define ABSTRACT_LOADABLE_FILE_H

#include "abstract_loadable_tree.h"

struct File_Version {
	int Major;
	int Minor;
	int Revision;
};

struct Cannot_Open_Exception : Parse_Exception {
	Cannot_Open_Exception(QString file_path)
	    : Parse_Exception({Parse_Exception_Code::Other, "Cannot open file '" + file_path + "'"}) {}
};

class Abstract_Loadable_File : public Abstract_Loadable_Tree {
 public:
	Abstract_Loadable_File(const File_Version Version);
	void load(QString file_path);
	QString version_string();

 private:
	struct Line_Context {
		QString key;
		QString value;
		int line_number;
		int key_line_number;
	};
	//
	State tokenize_line(QString trimmed_line, Line_Context& context);
	bool is_comment(QString line);
	int count_levels(QString line);
	void check_version_validity(Line_Context& context);
	void abort_parse(Parse_Exception& exception, Line_Context& context);
	QString msg_line(QString text, int line_number);

 private:
	File_Version Version;
	QString file_path;
};

#endif // ABSTRACT_LOADABLE_FILE_H
