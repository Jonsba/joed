#ifndef BACKEND_H
#define BACKEND_H

#include "abstract_loadable_tree.h"
#include "joed.h"

#include <QScopedPointer>
#include <QString>

class Escaper;
class Lua_Client;
class Lua_VM;

class QProcess;

struct File_Info {
	QString type;
	QString path;
};

class Backend final : public Abstract_Loadable_Tree {
 public:
	Backend(Lua_VM* lua_vm);
	~Backend();
	void reset_files_info(QString document_path);
	void write(QString code, QString file_path);
	void compile();
	File_Info* translated_document();
	File_Info* translated_environment();
	File_Info* compiled_document();
	QProcess* compile_process();
	Escaper* escaper();
	//
	inline static const QString Translated_Document_Id = "_translated_document_";
	inline static const QString Translated_Environment_Id = "_translated_environment_";
	inline static const QString Compiled_Document_Id = "_compiled_document_";
	inline static const QString PDF_Viewer_Id = "pdf";
	inline static const QString HTML_Viewer_Id = "html";

 private:
	State process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);
	//
	File_Info the_translated_document;
	File_Info the_translated_environment;
	File_Info the_compiled_document;
	QScopedPointer<Escaper> the_escaper;
	QScopedPointer<Lua_Client> lua_client;
	QScopedPointer<QProcess> the_compile_process;
};

#endif // BACKEND_H
