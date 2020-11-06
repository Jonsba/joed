#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "writer.h"
#include <QHash>

class Abstract_Block;
class Backend;
class Environment;
class Lua_VM;
class Styles;
class Root_Block;
class Writer;
class QProcess;

class Document : public Abstract_Loadable_File {
 public:
	Document(QString document_path = "");
	Backend* backend();
	Root_Block* root_block();
	QProcess* compile_process();
	void compile();
	void save_as(QString file_path);
	//
	inline static const File_Version Version = {1, 0, 0};
	inline static const QStringList End_Keys = {Joed::Keys[Style_E], Joed::Keys[Text_E]};
	inline static const QStringList Blocks_Keys = {Joed::Keys[Children_E], Joed::Keys[Block_E]};

 protected:
	State process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line = true);

 private:
	void create();
	void create(QString backend_name, QString document_class);
	void add_block(Abstract_Block* new_block);
	//
	Lua_VM* lua_vm;
	Backend* the_backend;
	Styles* styles;
	Environment* environment;
	Root_Block* the_root_block;
	QHash<int, Abstract_Block*> current_blocks;
	int block_level;
	Writer* writer;
};

#endif // DOCUMENT_H
