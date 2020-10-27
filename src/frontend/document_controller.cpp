#include "document_controller.h"
#include "multi_block_widget.h"
#include "src/abstract_multi_block.h"
#include "src/backend.h"
#include "src/document.h"

#include <QVBoxLayout>
#include <QVector>

Document_Controller::Document_Controller(QWidget* parent, QString document_path) {
	this->the_document = new Document(document_path);
	this->top_widget_block =
	    new Multi_Block_Widget(parent, (Abstract_Multi_Block*)this->the_document->root_block());
	parent->layout()->addWidget(this->top_widget_block);
}

void Document_Controller::compile() {
	this->the_document->compile();
}

QProcess* Document_Controller::compile_process() {
	return this->the_document->compile_process();
}

Document* Document_Controller::document() {
	return this->the_document;
}
