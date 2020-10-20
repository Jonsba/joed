#include <QFile>
#include <QString>
#include <QTextStream>

#include "backend.h"
#include "definitions_file.h"
#include "joed.h"
#include "joed_conf.h"
#include "parser.h"
#include "styles.h"

Parser::Parser() {}

void Parser::parse(QString the_file, Abstract_Loadable_Object* the_object) {
	QFile file(the_file);
	if (! file.open(QIODevice::ReadOnly)) {
		error("Cannot open file: " + the_file);
	}
	QTextStream stream(&file);
	QString line, trimmed_line;
	QString key;
	int level;
	State state = Starting;
	while (true) {
		switch (state) {
		case Parsing_Key:
			if (! read_key(trimmed_line, key)) {
				// It was the next line of a multiple lines value, which we need to parse as value
				state = Parsing_Value;
				continue;
			}
			state = the_object->process_intermediate_key(key, level);
			if (state == Parsing_Value && trimmed_line != "") {
				// We will check for one-liner
				continue;
			}
			break;
		case Parsing_Value:
			the_object->assign(key, trimmed_line);
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
		level = count_levels(line);
	}
}

bool Parser::is_comment(QString line) {
	if (line.mid(0, 2) == "--") {
		return true;
	}
	return false;
}

bool Parser::read_key(QString& trimmed_line, QString& key) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		return false;
	}
	key = trimmed_line.left(delimiter);
	trimmed_line = trimmed_line.mid(delimiter + 1).trimmed();
	return true;
}

int Parser::count_levels(QString line) {
	int i = 0;
	while (line[i] == '\t') {
		i++;
	}
	return i;
}

// DEBUG
// //////////////////////////////////////////////////////////////////////////////////////////

void Parser::print_indent(QString text, int level) {
	QString indentation = "";
	for (int i = 0; i < level; i++) {
		indentation += '\t';
	}
	print(indentation + text);
}
