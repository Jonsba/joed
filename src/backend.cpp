#include "backend.h"
#include "environment.h"
#include "escaper.h"
#include "joed.h"
#include "layout_block.h"
#include "lua_client.h"
#include "style.h"

#include <QFile>
#include <QProcess>

Backend::Backend(Lua_VM* lua_vm, QString name, QString document_class) {
	this->lua_client = new Lua_Client(lua_vm);
	this->the_escaper = new Escaper(lua_vm);
	this->the_name = name;
	this->the_document_class = document_class;
	this->the_compile_process = new QProcess();
}

QString Backend::name() {
	return this->the_name;
}

QString Backend::document_class() {
	return this->the_document_class;
}

State Backend::process_key(QString key, int level) {
	return State::Parsing_Value;
}

void Backend::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Joed::Keys[Output_E]) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	} else if (end_key == Joed::Keys[Doc_File_Ext_E]) {
		this->translated_document_path = BACKEND_WORKING_DIRECTORY DOCUMENT_BASENAME + value;
	} else if (end_key == Joed::Keys[Env_File_Ext_E]) {
		this->translated_environment_path =
		    BACKEND_WORKING_DIRECTORY + Environment::Basename_Id + value;
	} else if (end_key == Joed::Keys[Viewer_E]) {
		this->compiled_file_extension = value;
		this->the_compiled_document_path = BACKEND_WORKING_DIRECTORY DOCUMENT_BASENAME "." + value;
	} else if (end_key == Joed::Keys[Escape_Table_E]) {
		this->the_escaper->parse(value);
	}
}

void Backend::write_to_file(QString code, QString file_path) {
	QFile file(file_path);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(code.toUtf8());
	file.close();
}

void Backend::compile(QString document_code, QString environment_code) {
	this->write_to_file(document_code, this->translated_document_path);
	this->write_to_file(environment_code, this->translated_environment_path);
	//
	QHash<QString, QString> global_dict = {};
	global_dict[Translated_Document_Id] = this->translated_document_path;
	global_dict[Compiled_Document_Id] = this->the_compiled_document_path;
	QString exec_command = this->lua_client->eval_expr(global_dict);
	this->the_compile_process->setWorkingDirectory(BACKEND_WORKING_DIRECTORY);
	this->the_compile_process->start(exec_command);
}

QProcess* Backend::compile_process() {
	return this->the_compile_process;
}

QString Backend::compiled_document_path() {
	return this->the_compiled_document_path;
}

QString Backend::environment_path() {
	return this->translated_environment_path;
}

QString Backend::viewer_type() {
	return this->compiled_file_extension;
}

Escaper* Backend::escaper() {
	return this->the_escaper;
}
