#ifndef DEFINITIONS_PARSER_H
#define DEFINITIONS_PARSER_H

#include <QString>
#include <QVector>

class Joed_Conf;
class Styles;
class Backend;
class Abstract_Loadable_Object;

class Parser {
 public:
	Parser();
	void parse(QString the_file, Abstract_Loadable_Object* the_object);
	Styles* styles();
	Backend* backend();

 private:
	bool read_key(QString& trimmed_line, QString& key);
	void check_version_validity(QString version_string);
	void add_value_line(QString value_line);
	bool is_comment(QString line);
	int count_levels(QString line);
	//
	// DEBUG ///////////////////////////////////////////////////////////////////////////////////////
	void print_indent(QString text, int level);
};

#endif // DEFINITIONS_PARSER_H
