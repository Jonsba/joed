#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "abstract_loadable_file.h"

#include <QHash>
#include <QScopedPointer>

class Abstract_Block;
class Abstract_Multi_Block;
class Backend;
class Definitions_File;
class Environment;
class Layout_Block;
class Lua_VM;
class Root_Block;
class Document_Styles;
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
	//
	inline static const File_Version Version = {0, 0, 0};

 protected:
	void process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line = true);

 private:
	void create();
	//
	QString the_path;
	QScopedPointer<Lua_VM> lua_vm;
	QScopedPointer<Definitions_File> backend_definitions_file;
	QScopedPointer<Definitions_File> document_class_definitions_file;
	QScopedPointer<Backend> the_backend;
	QScopedPointer<Environment> environment;
	QScopedPointer<Document_Styles> styles;
	QScopedPointer<Root_Block> the_root_block;
	int key_level;
	QHash<int, Abstract_Multi_Block*> parent_blocks;
	Abstract_Block* current_block;
	QScopedPointer<Writer> writer;
};

#endif // DOCUMENT_H
