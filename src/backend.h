#ifndef BACKEND_H
#define BACKEND_H

#include "abstract_loadable_file.h"
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

struct Document_Class_Info {
	QString generic_class;
	QString backend_class;
};

class Backend final : public Abstract_Loadable_File {
 public:
	Backend(Lua_VM* lua_vm);
	~Backend();
	void load(QString name);
	void reset_files_info(QString document_path);
	void write(QString code, QString file_path);
	void compile();
	QString name();
	Document_Class_Info document_class(QString name);
	File_Info* translated_document();
	File_Info* translated_environment();
	File_Info* compiled_document();
	QProcess* compile_process();
	Escaper* escaper();
	//

 protected:
	const File_Version Version() { return {0, 1, 0}; }
	void process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value, int level, bool is_first_value_line);

 private:
	inline static const QString File_Extension = ".def";
	//
	QString the_name;
	QHash<QString, Document_Class_Info> document_classes;
	QString current_document_class;
	File_Info the_translated_document;
	File_Info the_translated_environment;
	File_Info the_compiled_document;
	QScopedPointer<Escaper> the_escaper;
	QScopedPointer<Lua_Client> lua_client;
	QScopedPointer<QProcess> the_compile_process;
};

#endif // BACKEND_H
