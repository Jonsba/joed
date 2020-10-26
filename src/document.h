#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "abstract_loadable_file.h"
#include <QHash>
#include <QString>

class Backend;
class Definitions_File;
class Joed_Conf_File;
class Layout_Block;
class Abstract_Block;
class QProcess;
class Styles;

class Document : public Abstract_Loadable_File {
 public:
	Document(QString document_path = "");
	State process_key(QString key, int level);
	void assign(QString end_key, QString value);
	void create(QString backend_name = "");
	void open(QString document_path);
	Layout_Block* root_block();
	QProcess* compile_process();
	void compile();
	//
	inline static const File_Version Version = {1, 0, 0};
	inline static const QStringList End_Keys = {Keys[Style_E], Keys[Text_E]};
	inline static const QStringList Blocks_Keys = {Keys[Children_E], Keys[Block_E]};

 private:
	void add_block(Abstract_Block* new_block);
	//
	Backend* backend;
	Joed_Conf_File* joed_conf_file;
	Definitions_File* definition_file;
	Styles* styles;
	Layout_Block* the_root_block;
	QHash<int, Abstract_Block*> current_blocks;
	int block_level;
};

#endif // DOCUMENT_H
