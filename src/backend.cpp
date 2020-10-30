#include "backend.h"
#include "joed.h"
#include "layout_block.h"
#include "lua_client.h"
#include "style.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>

Backend::Backend(Lua_VM* lua_vm) {
	this->lua_client = new Lua_Client(lua_vm);
	this->the_compile_process = new QProcess();
}

State Backend::process_key(QString key, int level) {
	return State::Parsing_Value;
}

void Backend::assign(QString end_key, QString value) {
	if (end_key == Keys[Name_E]) {
		this->name = value;
	} else if (end_key == Keys[Command_E]) {
		this->exec = value;
	} else if (end_key == Keys[File_Extension_E]) {
		this->translated_file_extension = value;
		this->translated_document_path = BACKEND_WORKING_DIRECTORY DOCUMENT_NAME + value;
	} else if (end_key == Keys[Viewer_E]) {
		this->compiled_file_extension = value;
		this->the_compiled_document_path = BACKEND_WORKING_DIRECTORY DOCUMENT_NAME "." + value;
	}
}

void Backend::compile(QString code) {
	QFile file(this->translated_document_path);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
	QHash<QString, QString> global_dict = {};
	global_dict[Translated_Document_Id] = this->translated_document_path;
	global_dict[Compiled_Document_Id] = this->the_compiled_document_path;
	QString exec_command = this->lua_client->eval(this->exec, global_dict);
	this->the_compile_process->setWorkingDirectory(BACKEND_WORKING_DIRECTORY);
	this->the_compile_process->start(exec_command);
}

QProcess* Backend::compile_process() {
	return this->the_compile_process;
}

QString Backend::compiled_document_path() {
	return this->the_compiled_document_path;
}

QString Backend::viewer_type() {
	return this->compiled_file_extension;
}
