#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "abstract_loadable_file.h"
#include <QHash>
#include <QString>

class Lua_VM;
class Backend;
class Environment;
class Joed_Conf_File;
class Top_Block;
class Abstract_Block;
class QProcess;
class Styles;
class Style;

class Document : public Abstract_Loadable_File {
 public:
	Document(QString document_path = "");
	State process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line = true);
	Backend* backend();
	void open(QString document_path);
	Top_Block* root_block();
	QProcess* compile_process();
	void compile();
	//
	inline static const File_Version Version = {1, 0, 0};
	inline static const QStringList End_Keys = {Keys[Style_E], Keys[Text_E]};
	inline static const QStringList Blocks_Keys = {Keys[Children_E], Keys[Block_E]};

 private:
	void create();
	void create(QString backend_name, QString document_class);
	void add_block(Abstract_Block* new_block);
	//
	Lua_VM* lua_vm;
	Backend* the_backend;
	Styles* styles;
	Environment* environment;
	Top_Block* the_root_block;
	QHash<int, Abstract_Block*> current_blocks;
	int block_level;
};

#endif // DOCUMENT_H
