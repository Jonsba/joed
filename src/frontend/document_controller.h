#ifndef DOCUMENT_CONTROLLER_H
#define DOCUMENT_CONTROLLER_H

#include <QString>

class Backend;
class Joed_Conf_File;
class Definitions_File;
class Document;
class Multi_Block;
class Multi_Block_Widget;
class Styles;
class QVBoxLayout;
class QProcess;

class Document_Controller {
 public:
	Document_Controller(QVBoxLayout* container_widget, QString document_path);
	QProcess* compile_process();
	void compile();

 private:
	void load_config();
	Backend* backend;
	Document* document;
	Multi_Block_Widget* top_widget_block;
};

#endif // DOCUMENT_CONTROLLER_H
