#include <QFile>
#include <QString>
#include <QTextStream>

#include "backend_translater.h"
#include "definitions_parser.h"
#include "joed.h"
#include "style_list.h"

Definitions_Parser::Definitions_Parser(Style_List *styles, Backend_Translater *compiler) {
	this->styles = styles;
	this->translater = compiler;
	this->Parse(Joed::Base_Definitions_File);
}
void Definitions_Parser::Parse(QString definition_file) {
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
		print("State: " + QString::number(state));
		switch (state) {
		case Parsing_Key: {
			QString key = Parse_Key(line, trimmed_line);
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
			Print_Indent("READ VALUE: " + trimmed_line);
			this->Add_Value_Line(trimmed_line);
			state = Parsing_Key;
			break;
		case Starting:
			state = Parsing_Key;
			break;
		}
		do {
			line = stream.readLine();
			if (line.isNull()) {
				return;
			}
			trimmed_line = line.trimmed();
		} while (trimmed_line == "" || Is_Comment(trimmed_line));
	}
	file.close();
}

bool Definitions_Parser::Is_Comment(QString line) {
	if (line.mid(0, 2) == "--") {
		return true;
	}
	return false;
}

QString Definitions_Parser::Parse_Key(QString line, QString &trimmed_line) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		return "";
	}
	QString current_key = trimmed_line.left(delimiter);
	for (QString key : Joed::Keys) {
		if (current_key == key) {
			int counted_levels = Count_Levels(line);
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
				this->styles->Add_Style(current_key);
			}
			Print_Indent("READ KEY: " + To_String(this->keys_hierarchy));
			trimmed_line = trimmed_line.mid(delimiter + 1).trimmed();
			this->current_key = current_key;
			return current_key;
		}
	}
	return "";
}

int Definitions_Parser::Count_Levels(QString line) {
	int i = 0;
	while (line[i] == '\t') {
		i++;
	}
	return i;
}

void Definitions_Parser::Add_Value_Line(QString value_line) {
	if (this->current_key == Joed::Version_Key) {
		Check_Version_Validity(value_line);
	} else if (this->current_key == Joed::Backend_Key) {
		this->translater->Set_Backend(value_line);
	} else if (this->keys_hierarchy[0] == Joed::Styles_Key) {
		this->styles->Add_Value(this->current_key, value_line);
	}
}

void Definitions_Parser::Check_Version_Validity(QString version_string) {
	if (false) {
		print("Invalid version: " + version_string);
		throw;
	}
}

// DEBUG //////////////////////////////////////////////////////////////////////////////////////////

void Definitions_Parser::Print_Indent(QString text) {
	QString indentation = "";
	for (int i = 0; i < this->level; i++) {
		indentation += '\t';
	}
	print(indentation + text);
}

QString Definitions_Parser::To_String(QString string_vector[]) {
	QString result = string_vector[0];
	for (int i = 1; i < Max_Ident_Level; i++) {
		if (string_vector[i] == "") break;
		result += "." + string_vector[i];
	}
	return result;
}
