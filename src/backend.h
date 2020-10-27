#ifndef BACKEND_H
#define BACKEND_H

#include "abstract_loadable_tree.h"
#include "joed.h"
#include <QString>
#include <QVector>

#define DOCUMENT_NAME "document"
#define TEX_WORKING_DIRECTORY "/home/jonas-travail/Documents/github/joed/build/tex/"

class Lua_VM;
class Lua_Client;
class QProcess;

class Backend : public Abstract_Loadable_Tree {
 public:
	Backend(Lua_VM* lua_vm);
	State process_key(QString key, int level);
	void assign(QString end_key, QString value);
	QProcess* compile_process();
	void compile(QString code);
	QString compiled_document_path();
	//
	inline static const QString Translated_Document_Id = "_translated_document_";
	inline static const QString Compiled_Document_Id = "_compiled_document_";

 private:
	Lua_Client* lua_client;
	QString name;
	QString exec;
	QString translated_file_extension;
	QString compiled_file_extension;
	QString translated_document_path;
	QString the_compiled_document_path;
	QProcess* the_compile_process;
};

#endif // BACKEND_H
