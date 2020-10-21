#ifndef ABSTRACT_LOADABLE_FILE_H
#define ABSTRACT_LOADABLE_FILE_H

#include "abstract_loadable_object.h"

struct File_Version {
	int Major;
	int Minor;
	int Revision;
};

class Abstract_Loadable_File : public Abstract_Loadable_Object {
 public:
	Abstract_Loadable_File(const File_Version Version);
	void check_version_validity(QString version_string);
	//
	const QString Version_Key = "format-version";
	void parse(QString file_path);

 private:
	bool read_key(QString& trimmed_line, QString& key);
	void add_value_line(QString value_line);
	bool is_comment(QString line);
	int count_levels(QString line);
	//
	// DEBUG ///////////////////////////////////////////////////////////////////////////////////////
	void print_indent(QString text, int level);

 private:
	File_Version Version;
};

#endif // ABSTRACT_LOADABLE_FILE_H
