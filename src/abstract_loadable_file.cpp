#include "abstract_loadable_file.h"
#include "joed.h"

#include <QFile>

Abstract_Loadable_File::Abstract_Loadable_File() {}

void Abstract_Loadable_File::load(QString file_path) {
	this->file_path = file_path;
	QFile file_descr(file_path);
	if (! file_descr.open(QIODevice::ReadOnly)) {
		throw Exceptions::Cannot_Open(file_path);
	}
	QString line, trimmed_line;
	int level = 0, last_key_level = 0;
	bool is_first_value_line;
	State state = State::Parsing_Version;
	Line_Context context = {"", "", 0, 0};
	while (true) {
		// A) We read the next line and interpret it
		do {
			line = file_descr.readLine();
			context.line_number++;
			if (line.isNull()) {
				file_descr.close();
				return;
			}
			trimmed_line = line.trimmed();
		} while (trimmed_line == "" || is_comment(line));
		level = count_levels(line);
		switch (state) {
		case State::Parsing_Version:
			this->tokenize_line(trimmed_line, context);
			break;
		case State::Parsing_Key:
			state = this->tokenize_line(trimmed_line, context);
			break;
		default:
			state = State::Parsing_Value;
			if (level > last_key_level) {
				context.value = trimmed_line;
			} else { // Does the counted level imply that we are reading a new (end_)key?
				state = this->tokenize_line(trimmed_line, context);
			}
		}
		// B) We finalize line processing and send the processed data to the client that needs it
		while (true) {
			try {
				switch (state) {
				case State::Parsing_Version:
					this->check_version_validity(context);
					state = State::Parsing_Key;
					break;
				case State::Parsing_Key:
					set_last_key_level(last_key_level, level);
					this->process_intermediate_key(context.key, level);
					break;
				case State::Parsing_End_Key:
					set_last_key_level(last_key_level, level);
					state = State::Parsing_Value;
					is_first_value_line = true;
					// Do we have a one-liner to be processed before reading the next line?
					if (context.value != "") {
						continue;
					}
					break;
				case State::Parsing_Value:
					this->assign(context.key, context.value, last_key_level, is_first_value_line);
					is_first_value_line = false;
					break;
				}
			} catch (Exception& exception) {
				this->abort_parse(exception, context);
			}
			break;
		}
	}
}

QString Abstract_Loadable_File::version_string() {
	return QString::number(this->Version().Major) + "." + QString::number(this->Version().Minor) +
	       "." + QString::number(this->Version().Revision);
}

void Abstract_Loadable_File::check_version_validity(Line_Context& context) {
	if (context.key != Field::Key::Version) {
		throw Exception("Expected '" + Field::Key::Version + " := <x>.<y>.<z>' at first line");
	}
	QStringList version_list = context.value.split(".");
	int major_version = version_list[0].toInt();
	int minor_version = version_list[1].toInt();
	if (major_version != Version().Major || minor_version > Version().Minor) {
		throw Exception("Unsupporter version: " + context.value + '\n' + "Any version between " +
		                QString::number(Version().Major) + ".0.0 and " +
		                QString::number(Version().Major) + "." + QString::number(Version().Minor) +
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

State Abstract_Loadable_File::tokenize_line(QString trimmed_line, Line_Context& context) {
	int delimiter = trimmed_line.indexOf(':');
	if (delimiter < 0) {
		msg_line("expected key, got: " + trimmed_line, context.line_number);
	}
	context.key = trimmed_line.left(delimiter).trimmed();
	context.key_line_number = context.line_number;
	delimiter++;
	State next_state = State::Parsing_Key;
	if (trimmed_line[delimiter] == '=') {
		delimiter++;
		next_state = State::Parsing_End_Key;
	}
	context.value = trimmed_line.mid(delimiter).trimmed();
	return next_state;
}

int Abstract_Loadable_File::count_levels(QString line) {
	int i = 0;
	while (line[i] == '\t') {
		i++;
	}
	return i;
}

void Abstract_Loadable_File::set_last_key_level(int& last_key_level, int level) {
	if (level > last_key_level + 1) {
		throw Exceptions::Invalid_Indent();
	}
	last_key_level = level;
}

void Abstract_Loadable_File::abort_parse(Exception& exception, Line_Context& context) {
	switch (exception.code) {
	case Exception_Code::Invalid_Key:
		// If an assign statement that didn't evaluate a one-liner returned this error, it means that
		// the current line is no longer the line with the key. That's why we use key_line_number here
		exception.msg = msg_line("invalid key '" + context.key + "'", context.key_line_number);
		break;
	case Exception_Code::Invalid_Value:
		exception.msg =
			 msg_line("invalid value '" + context.value + "' for key '" + context.key + "'",
		             context.line_number);
		break;
	case Exception_Code::Invalid_Indent:
		exception.msg =
			 msg_line("invalid indentation for key '" + context.key + "'", context.line_number);
		break;
	case Exception_Code::Other:
		exception.msg = msg_line(exception.msg, context.line_number);
		break;
	case Exception_Code::Processed:
		exception.msg = msg_line("Error while processing line: ", context.line_number) + "\n\t" +
		                exception.msg.replace("\n", "\n\t");
		break;
	}
	exception.code = Exception_Code::Processed;
	throw exception;
}

QString Abstract_Loadable_File::msg_line(QString msg, int line_number) {
	return "File: '" + this->file_path + "'\n" + "Line: " + QString::number(line_number) + '\n' +
	       "Error: " + msg;
}
