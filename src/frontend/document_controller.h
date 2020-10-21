#ifndef DOCUMENT_CONTROLLER_H
#define DOCUMENT_CONTROLLER_H

#include <QString>

class Joed_Conf;
class Definitions_File;
class Parser;
class Styles;
class Multi_Block;
class Multi_Block_Widget;
class Backend;
class QVBoxLayout;
class QProcess;

class Document_Controller {
 public:
	Document_Controller(QVBoxLayout* container_widget, QProcess* compile_process,
	                    QString document_path);
	void new_document(QVBoxLayout* widget_container);
	void open(QVBoxLayout* widget_container, QString document_path);
	void compile();

 private:
	void load_config();
	Parser* parser;
	Joed_Conf* joed_conf;
	Definitions_File* definition_file;
	Styles* styles;
	Backend* backend;
	Multi_Block* top_block;
	Multi_Block_Widget* top_widget_block;
};

#endif // DOCUMENT_CONTROLLER_H
