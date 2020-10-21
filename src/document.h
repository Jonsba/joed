#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "abstract_loadable_file.h"
#include <QString>

class Backend;
class Definitions_File;
class Joed_Conf_File;
class Multi_Block;
class QProcess;
class Styles;

class Document : public Abstract_Loadable_File {
 public:
	Document(QString document_path = "");
	State process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value);
	void create();
	void open(QString document_path);
	Multi_Block* root_block();
	QProcess* compile_process();
	void compile();
	//
	inline static const File_Version Version = {1, 0, 0};

 private:
	Backend* backend;
	Joed_Conf_File* joed_conf;
	Definitions_File* definition_file;
	Styles* styles;
	Multi_Block* the_root_block;
};

#endif // DOCUMENT_H
