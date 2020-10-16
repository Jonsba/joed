#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>

#define DOCUMENT_NAME "document"
#define TEX_DOCUMENT DOCUMENT_NAME ".tex"
#define TEX_WORKING_DIRECTORY "/home/jonas-travail/Documents/github/joed/build/tex/"
#define TEX_DOCUMENT_PATH TEX_WORKING_DIRECTORY TEX_DOCUMENT
#define PDF_DOCUMENT_PATH TEX_WORKING_DIRECTORY DOCUMENT_NAME ".pdf"

class Definitions_Parser;
class Styles;
class Multi_Block;
class Multi_Block_Widget;
class Compile_Env;
class QVBoxLayout;
class QProcess;

class Document_Root {
 public:
	Document_Root(QVBoxLayout* container_widget, QProcess* compile_process);
	void Compile_Document();

 private:
	Styles* styles;
	Multi_Block* top_block;
	Multi_Block_Widget* top_widget_block;
	Compile_Env* compile_env;
	QProcess* compile_process;
};

#endif // DOCUMENT_H
