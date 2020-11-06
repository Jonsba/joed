#ifndef BACKEND_H
#define BACKEND_H

#include "abstract_loadable_tree.h"
#include "joed.h"
#include <QString>

#define DOCUMENT_BASENAME "document"
#define BACKEND_WORKING_DIRECTORY "/home/jonas-travail/Documents/github/joed/build/document/"

class Lua_Client;
class Lua_VM;
class Escaper;
class QProcess;

class Backend : public Abstract_Loadable_Tree {
 public:
	Backend(Lua_VM* lua_vm, QString name, QString document_class);
	QString name();
	QString document_class();
	QProcess* compile_process();
	void compile(QString document_code, QString environment_code);
	QString compiled_document_path();
	QString environment_path();
	QString viewer_type();
	Escaper* escaper();

	//
	inline static const QString Translated_Document_Id = "_translated_document_";
	inline static const QString Compiled_Document_Id = "_compiled_document_";
	inline static const QString PDF_Viewer_Id = "pdf";
	inline static const QString HTML_Viewer_Id = "html";

 private:
	State process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);
	void write_to_file(QString code, QString file_path);
	//
	Lua_Client* lua_client;
	QString the_name;
	QString the_document_class;
	QString translated_document_path;
	QString translated_environment_path;
	QString compiled_file_extension;
	QString the_compiled_document_path;
	QProcess* the_compile_process;
	Escaper* the_escaper;
};

#endif // BACKEND_H
