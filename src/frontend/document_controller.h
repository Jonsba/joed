#ifndef DOCUMENT_CONTROLLER_H
#define DOCUMENT_CONTROLLER_H

#include <QString>

class Backend;
class Document;
class Multi_Block_Widget;
class QWidget;
class QProcess;

class Document_Controller {
 public:
	Document_Controller(QWidget* parent, QString document_path);
	void compile();
	QProcess* compile_process();
	Document* document();

 private:
	void Compilation_Completed();
	Document* the_document;
	Multi_Block_Widget* top_widget_block;
};

#endif // DOCUMENT_CONTROLLER_H
