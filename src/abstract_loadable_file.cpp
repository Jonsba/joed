#include "abstract_loadable_file.h"
#include "joed.h"

#include <QFile>
#include <QTextStream>

Abstract_Loadable_File::Abstract_Loadable_File(const File_Version Version) {
	this->Version = Version;
}

void Abstract_Loadable_File::check_version_validity(QString version_string) {
	QStringList version_list = version_string.split(".");
	int major_version = version_list.at(0).toInt();
	int minor_version = version_list.at(1).toInt();
	if (major_version != Version.Major || minor_version > Version.Minor) {
		print("Unsupporter version: " + version_string);
		error("Any version between " + QString::number(Version.Major) + ".0.0 and " +
		      QString::number(Version.Major) + "." + QString::number(Version.Minor) +
		      ".x are supported");
	}
}

void Abstract_Loadable_File::parse(QString file_path) {
	QFile file(file_path);
	if (! file.open(QIODevice::ReadOnly)) {
		error("Cannot open file: " + file_path);
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
			state = this->process_intermediate_key(key, level);
			if (state == Parsing_Value && trimmed_line != "") {
				// We will check for one-liner
				continue;
			}
			break;
		case Parsing_Value:
			this->assign(key, trimmed_line);
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
	key = trimmed_line.left(delimiter);
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
	print(indentation + text);
}
