#include "abstract_loadable_file.h"
#include "joed.h"

#include <QFile>

Abstract_Loadable_File::Abstract_Loadable_File(const File_Version Version) {
	this->Version = Version;
}

void Abstract_Loadable_File::load(QString file_path) {
	QFile file_descr(file_path);
	if (! file_descr.open(QIODevice::ReadOnly)) {
		error("Cannot load file: " + file_path);
	}
	QString line, trimmed_line;
	QString key;
	int level;
	bool is_first_value_line;
	State state = State::Starting;
	while (true) {
		switch (state) {
		case State::Parsing_Key:
			if (! read_key(trimmed_line, key)) {
				// It was the next line of a multiple lines value, which we need to parse as value
				state = State::Parsing_Value;
				continue;
			}
			is_first_value_line = true;
			if (key == Joed::Keys[Version_E]) {
				state = State::Parsing_Value;
			} else {
				state = this->process_key(key, level);
			}
			if (state == State::Parsing_Value && trimmed_line != "") {
				// We will check for one-liner
				continue;
			}
			break;
		case State::Parsing_Value:
			if (key == Joed::Keys[Version_E]) {
				this->check_version_validity(trimmed_line);
			} else {
				this->assign(key, trimmed_line, is_first_value_line);
			}
			is_first_value_line = false;
			// We assume that the next line will be a key, and when it fails, we would be dealing with
			// a multiline value
			state = State::Parsing_Key;
			break;
		case State::Starting:
			state = State::Parsing_Key;
			break;
		}
		do {
			line = file_descr.readLine();
			if (line.isNull()) {
				file_descr.close();
				return;
			}
			trimmed_line = line.trimmed();
		} while (trimmed_line == "" || is_comment(trimmed_line));
		level = count_levels(line);
	}
}

QString Abstract_Loadable_File::version_string() {
	return QString::number(this->Version.Major) + "." + QString::number(this->Version.Minor) + "." +
	       QString::number(this->Version.Revision);
}

void Abstract_Loadable_File::check_version_validity(QString version_string) {
	QStringList version_list = version_string.split(".");
	int major_version = version_list[0].toInt();
	int minor_version = version_list[1].toInt();
	if (major_version != Version.Major || minor_version > Version.Minor) {
		echo("Unsupporter version: " + version_string);
		error("Any version between " + QString::number(Version.Major) + ".0.0 and " +
		      QString::number(Version.Major) + "." + QString::number(Version.Minor) +
		      ".x are supported");
	}
}

bool Abstract_Loadable_File::is_comment(QString line) {
	if (line.mid(0, 2) == "--") {
		return true;
	}
	return false;
}

bool Abstract_Loadable_File::read_key(QString& trimmed_line, QString& key) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		return false;
	}
	QString potential_key = trimmed_line.left(delimiter);
	for (int i = 0; i < potential_key.length(); i++) {
		if (! potential_key[i].isLetter() && potential_key[i] != '-') {
			return false;
		}
	}
	key = potential_key;
	trimmed_line = trimmed_line.mid(delimiter + 1).trimmed();
	return true;
}

int Abstract_Loadable_File::count_levels(QString line) {
	int i = 0;
	while (line[i] == '\t') {
		i++;
	}
	return i;
}

// DEBUG
// //////////////////////////////////////////////////////////////////////////////////////////

void Abstract_Loadable_File::print_indent(QString text, int level) {
	QString indentation = "";
	for (int i = 0; i < level; i++) {
		indentation += '\t';
	}
	echo(indentation + text);
}
