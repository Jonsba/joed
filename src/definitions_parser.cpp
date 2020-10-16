#include <QFile>
#include <QString>
#include <QTextStream>

#include "compile_env.h"
#include "definitions_parser.h"
#include "joed.h"
#include "styles.h"

Definitions_Parser::Definitions_Parser(Initializer<Styles>* style_initializer,
                                       Initializer<Compile_Env>* compiler) {
	this->style_initializer = style_initializer;
	this->compiler_initializer = compiler;
	this->parse(Joed::Base_Definitions_File);
}
void Definitions_Parser::parse(QString definition_file) {
	QFile file(definition_file);
	if (! file.open(QIODevice::ReadOnly)) {
		print("Cannot open definitions file: " + definition_file);
		throw;
	}
	QTextStream stream(&file);
	QString line, trimmed_line;
	State state = Starting;
	this->level = 0;
	while (true) {
		switch (state) {
		case Parsing_Key: {
			QString key = read_key(trimmed_line);
			state = parse_identifier(key, line);
			if (state == Parsing_Value && trimmed_line != "") {
				// We will check for one-liner
				continue;
			}
			break;
		}
		case Parsing_Value:
			this->add_value_line(trimmed_line);
			state = Parsing_Key;
			break;
		case Starting:
			state = Parsing_Key;
			break;
		}
		do {
			line = stream.readLine();
			if (line.isNull()) {
				file.close();
				return;
			}
			trimmed_line = line.trimmed();
		} while (trimmed_line == "" || is_comment(trimmed_line));
	}
}

bool Definitions_Parser::is_comment(QString line) {
	if (line.mid(0, 2) == "--") {
		return true;
	}
	return false;
}

QString Definitions_Parser::read_key(QString& trimmed_line) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		return "";
	}
	QString key = trimmed_line.left(delimiter);
	trimmed_line = trimmed_line.mid(delimiter + 1).trimmed();
	return key;
}

int Definitions_Parser::count_levels(QString line) {
	int i = 0;
	while (line[i] == '\t') {
		i++;
	}
	return i;
}

State Definitions_Parser::parse_identifier(QString key, QString line) {
	if (count_levels(line) == 0) {
		return parse_top_key(key);
	}
	if (this->top_key == Backend_Key) {
		return this->compiler_initializer->parse_identifier(key);
	} else {
		return this->style_initializer->parse_identifier(key);
	}
}

State Definitions_Parser::parse_top_key(QString key) {
	if (key == Version_Key) {
		this->top_key = Version_Key;
		return Parsing_Value;
	} else if (key == Backend_Key) {
		this->top_key = Backend_Key;
	} else if (key == Styles_Key) {
		this->top_key = Styles_Key;
	} else {
		print("Invalid top key: " + key);
		throw;
	}
	return Parsing_Key;
}

void Definitions_Parser::add_value_line(QString value_line) {
	if (this->top_key == Version_Key) {
		check_version_validity(value_line);
	} else if (this->top_key == Backend_Key) {
		this->compiler_initializer->add_value(value_line);
	} else {
		this->style_initializer->add_value(value_line);
	}
}

void Definitions_Parser::check_version_validity(QString version_string) {
	QStringList version_list = version_string.split(".");
	int major_version = version_list.at(0).toInt();
	int minor_version = version_list.at(1).toInt();
	if (major_version != Major_Version || minor_version > Minor_Version) {
		print("Unsupporter version: " + version_string);
		print("Any version between " + QString::number(Major_Version) + ".0.0 and " +
		      QString::number(Major_Version) + "." + QString::number(Minor_Version) +
		      ".x are supported");
		throw;
	}
}

// DEBUG //////////////////////////////////////////////////////////////////////////////////////////

void Definitions_Parser::print_indent(QString text) {
	QString indentation = "";
	for (int i = 0; i < this->level; i++) {
		indentation += '\t';
	}
	print(indentation + text);
}

QString Definitions_Parser::to_string(QString string_vector[]) {
	QString result = string_vector[0];
	for (int i = 1; i < Max_Ident_Level; i++) {
		if (string_vector[i] == "") break;
		result += "." + string_vector[i];
	}
	return result;
}
