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
	int level = 0, last_key_level;
	bool is_first_value_line;
	State state = State::Parsing_Version;
	while (true) {
		// A) We read the next line and interpret it
		do {
			line = file_descr.readLine();
			if (line.isNull()) {
				file_descr.close();
				return;
			}
			trimmed_line = line.trimmed();
		} while (trimmed_line == "" || is_comment(line));
		level = count_levels(line);
		switch (state) {
		case State::Parsing_Version:
			this->read_key(trimmed_line, key);
			break;
		case State::Parsing_Key:
			state = this->read_key(trimmed_line, key);
			break;
		default:
			state = State::Parsing_Value;
			// Does the counted level imply that we are reading a new key?
			if (level <= last_key_level) {
				state = this->read_key(trimmed_line, key);
			}
		}
		// B) We finalize line processing and send the processed data to the client that needs it
		while (true) {
			switch (state) {
			case State::Parsing_Version:
				this->check_version_validity(trimmed_line);
				state = State::Parsing_Key;
				break;
			case State::Parsing_Key:
				last_key_level = level;
				this->process_key(key, level);
				break;
			case State::Parsing_End_Key:
				last_key_level = level;
				state = State::Parsing_Value;
				is_first_value_line = true;
				if (trimmed_line != "") {
					// We first check for one-liner before reading the next line
					continue;
				}
				break;
			case State::Parsing_Value:
				this->assign(key, trimmed_line, is_first_value_line);
				is_first_value_line = false;
				break;
			}
			break;
		}
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
	int i;
	for (i = 0; line[i] == '\t'; i++)
		;
	if (line.mid(i, 2) == "--") {
		return true;
	}
	return false;
}

State Abstract_Loadable_File::read_key(QString& trimmed_line, QString& key) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		error("Expected key, got: " + trimmed_line);
	}
	key = trimmed_line.left(delimiter).trimmed();
	delimiter++;
	State next_state = State::Parsing_Key;
	if (trimmed_line[delimiter] == '=') {
		delimiter++;
		next_state = State::Parsing_End_Key;
	}
	trimmed_line = trimmed_line.mid(delimiter).trimmed();
	return next_state;
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
