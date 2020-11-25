#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "abstract_loadable_file.h"

#include <QHash>
#include <QScopedPointer>

class Abstract_Block;
class Abstract_Multi_Block;
class Backend;
class Document_Class;
class Environment;
class Layout_Block;
class Lua_VM;
class Root_Block;
class Styles;
class Writer;

class QProcess;

class Document final : public Abstract_Loadable_File {
 public:
	Document(QString the_path = "");
	~Document();
	Backend* backend();
	Root_Block* root_block();
	QString path();
	void save();
	void save_as(QString file_path);
	QProcess* compile_process();
	void compile();

 protected:
	const File_Version Version() { return {0, 0, 0}; }
	void process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value, int level, bool is_first_value_line = true);

 private:
	void create();
	//
	QString the_path;
	QScopedPointer<Lua_VM> lua_vm;
	QScopedPointer<Backend> the_backend;
	QScopedPointer<Document_Class> document_class;
	QScopedPointer<Environment> environment;
	QScopedPointer<Styles> styles;
	QScopedPointer<Root_Block> the_root_block;
	QHash<int, Abstract_Multi_Block*> parent_blocks;
	Abstract_Block* current_block;
	QScopedPointer<Writer> writer;
};

#endif // DOCUMENT_H
