#ifndef DEFINITIONS_PARSER_H
#define DEFINITIONS_PARSER_H

#include <QString>

class Styles;
class Compile_Env;

class Definitions_Parser {
 public:
	static const int Max_Ident_Level = 3;
	Definitions_Parser(Styles* styles, Compile_Env* compiler);

 private:
	static const int Major_Version = 1;
	static const int Minor_Version = 0;
	static const int Revision_Version = 0;
	//
	void parse(QString definition_file);
	QString parse_key(QString line, QString& trimmed_line);
	void check_version_validity(QString version_string);
	void add_value_line(QString value_line);
	bool is_comment(QString line);
	int count_levels(QString line);
	//
	QString keys_hierarchy[Max_Ident_Level];
	Styles* styles;
	Compile_Env* compiler;
	QString current_key;
	int level;
	// DEBUG ///////////////////////////////////////////////////////////////////////////////////////
	void print_indent(QString text);
	QString to_string(QString string_vector[]);
};

#endif // DEFINITIONS_PARSER_H
