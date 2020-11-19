#include "backend.h"
#include "environment.h"
#include "escaper.h"
#include "joed.h"
#include "layout_block.h"
#include "lua_client.h"
#include "style.h"

#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTemporaryDir>

Backend::Backend(Lua_VM* lua_vm) {
	this->the_compile_process.reset(new QProcess());
	this->the_escaper.reset(new Escaper(lua_vm));
	this->lua_client.reset(new Lua_Client(lua_vm));
}

void Backend::reset_files_info(QString document_path) {
	QFileInfo document_file;
	if (document_path != "") {
		document_file.setFile(document_path);
	} else {
		QTemporaryDir temp_dir;
		document_file.setFile(temp_dir.path());
	}
	QString document_base_name = document_file.baseName();
	QString working_directory = document_file.path() + Joed::Sep + document_base_name + Joed::Sep;

	QDir dir(working_directory);
	if (! dir.exists()) {
		dir.mkdir(working_directory);
	}
	this->the_translated_document.path =
	    working_directory + document_base_name + "." + this->the_translated_document.type;
	this->the_translated_environment.path =
	    working_directory + Environment::Name_Id + "." + this->the_translated_environment.type;
	this->the_compiled_document.path =
	    working_directory + document_base_name + "." + this->the_compiled_document.type;
	this->the_compile_process->setWorkingDirectory(working_directory);
}

void Backend::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Field::Key::Output) {
		this->lua_client->add_expr_line(value, is_first_value_line);
	} else if (end_key == Field::Key::Doc_File_Ext) {
		this->the_translated_document.type = value;
	} else if (end_key == Field::Key::Env_File_Ext) {
		this->the_translated_environment.type = value;
	} else if (end_key == Field::Key::Viewer) {
		this->the_compiled_document.type = value;
	} else if (end_key == Field::Key::Escape_Table) {
		this->the_escaper->parse(value);
	} else {
		throw Invalid_Key_Exception();
	}
}

void Backend::compile() {
	QHash<QString, QString> global_dict = {};
	global_dict[Field::Id::Translated_Document] = '"' + this->the_translated_document.path + '"';
	global_dict[Field::Id::Translated_Environment] =
	    '"' + this->the_translated_environment.path + '"';
	global_dict[Field::Id::Compiled_Document] = '"' + this->the_compiled_document.path + '"';
	QString exec_command = this->lua_client->eval_expr(global_dict);
	this->the_compile_process->start(exec_command);
}

void Backend::write(QString code, QString file_path) {
	QFile file(file_path);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(code.toUtf8());
	file.close();
}

QProcess* Backend::compile_process() {
	return this->the_compile_process.get();
}

File_Info* Backend::translated_document() {
	return &this->the_translated_document;
}
File_Info* Backend::translated_environment() {
	return &this->the_translated_environment;
}
File_Info* Backend::compiled_document() {
	return &this->the_compiled_document;
}

Escaper* Backend::escaper() {
	return this->the_escaper.get();
}

Backend::~Backend() = default;
