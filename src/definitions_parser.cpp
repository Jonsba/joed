#include <QFile>
#include <QString>
#include <QTextStream>

#include "compile_env.h"
#include "definitions_parser.h"
#include "joed.h"
#include "styles.h"

Definitions_Parser::Definitions_Parser(Styles* styles, Compile_Env* compiler) {
	this->styles = styles;
	this->compiler = compiler;
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
	enum State { Starting = 0, Parsing_Key = 1, Check_For_Oneliner = 2, Parsing_Value = 3 };
	State state = Starting;
	this->level = 0;
	while (true) {
		switch (state) {
		case Parsing_Key: {
			QString key = parse_key(line, trimmed_line);
			if (key != "") {
				state = Check_For_Oneliner;
				this->level++;
			} else {
				state = Parsing_Value;
			}
			continue;
		}
		case Check_For_Oneliner:
			if (trimmed_line != "") { // One-liner found?
				// Then we will parse the value
				state = Parsing_Value;
				continue;
			}
			// Then a key or some data has to be read at the next line
			state = Parsing_Key;
			break;
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

QString Definitions_Parser::parse_key(QString line, QString& trimmed_line) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		return "";
	}
	QString current_key = trimmed_line.left(delimiter);
	for (QString key : Joed::Keys) {
		if (current_key == key) {
			int counted_levels = count_levels(line);
			if (counted_levels < this->level) {
				for (int i = counted_levels + 1; i < this->level; i++) {
					this->keys_hierarchy[i] = "";
				}
			}
			this->level = counted_levels;
			this->keys_hierarchy[this->level] = current_key;
			if (counted_levels == 1) {
				if (keys_hierarchy[0] != "styles") {
					print("Unexpected structure for the definitions file");
					throw;
				}
				this->styles->parse_style_identifier(current_key);
			}
			trimmed_line = trimmed_line.mid(delimiter + 1).trimmed();
			this->current_key = current_key;
			return current_key;
		}
	}
	return "";
}

int Definitions_Parser::count_levels(QString line) {
	int i = 0;
	while (line[i] == '\t') {
		i++;
	}
	return i;
}

void Definitions_Parser::add_value_line(QString value_line) {
	if (this->current_key == Joed::Version_Key) {
		check_version_validity(value_line);
	} else if (this->current_key == Joed::Backend_Key) {
		this->compiler->set_backend(value_line);
	} else if (this->keys_hierarchy[0] == Joed::Styles_Key) {
		this->styles->add_value(this->current_key, value_line);
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
