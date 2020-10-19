#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "initializer.h"
#include <QString>

class Styles;

class Definitions_Parser;
class Styles;
class Multi_Block;
class Multi_Block_Widget;
class Backend;
class QVBoxLayout;
class QProcess;

class Document {
 public:
	Document(QVBoxLayout* container_widget, QProcess* compile_process);
	void compile();

 private:
	Initializer<Styles>* styles_initializer;
	Styles* styles;
	Initializer<Backend>* backend_initializer;
	Backend* backend;
	Multi_Block* top_block;
	Multi_Block_Widget* top_widget_block;
};

#endif // DOCUMENT_H
