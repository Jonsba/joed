#ifndef DEFINITIONS_PARSER_H
#define DEFINITIONS_PARSER_H

#include "initializer.h"
#include <QString>
#include <QVector>

class Styles;
class Compile_Env;
class Abstract_Buildable_Object;

class Definitions_Parser {
 public:
	static const int Max_Ident_Level = 3;
	Definitions_Parser(Initializer<Styles>* style_initializer,
	                   Initializer<Compile_Env>* compiler_initializer);

 private:
	static const int Major_Version = 1;
	static const int Minor_Version = 0;
	static const int Revision_Version = 0;
	const QString Version_Key = "version";
	const QString Backend_Key = "backend";
	const QString Styles_Key = "styles";
	const QString_Vector Top_Keys = {Version_Key, Backend_Key, Styles_Key};

	//
	void parse(QString definition_file);
	QString read_key(QString& trimmed_line);
	State parse_top_key(QString key);
	void check_version_validity(QString version_string);
	void add_value_line(QString value_line);
	bool is_comment(QString line);
	int count_levels(QString line);
	State parse_identifier(QString key, QString line);
	//
	QString keys_hierarchy[Max_Ident_Level];
	Initializer<Styles>* style_initializer;
	Initializer<Compile_Env>* compiler_initializer;
	QString top_key;
	QString current_key;
	int level;
	// DEBUG ///////////////////////////////////////////////////////////////////////////////////////
	void print_indent(QString text);
	QString to_string(QString string_vector[]);
};

#endif // DEFINITIONS_PARSER_H
