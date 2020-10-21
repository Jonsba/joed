#include "document_controller.h"
#include "multi_block_widget.h"
#include "src/backend.h"
#include "src/document.h"

#include <QProcess>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>

Document_Controller::Document_Controller(QVBoxLayout* widget_container, QString document_path) {
	this->document = new Document(document_path);
	this->top_widget_block = new Multi_Block_Widget(widget_container, this->document->root_block());
}

void Document_Controller::compile() {
	this->document->compile();
}

QProcess* Document_Controller::compile_process() {
	return this->document->compile_process();
}
