#include "document_controller.h"
#include "multi_block_widget.h"
#include "src/backend.h"
#include "src/definitions_file.h"
#include "src/joed_conf.h"
#include "src/multi_block.h"
#include "src/parser.h"
#include "src/style.h"
#include "src/styles.h"

#include <QProcess>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>

Document_Controller::Document_Controller(QVBoxLayout* widget_container, QProcess* compile_process,
                                         QString document_path) {
	this->parser = new Parser();
	if (document_path == "") {
		this->new_document(widget_container);
	} else {
		this->open(widget_container, document_path);
	}
	this->backend->set_compile_process(compile_process);
}

void Document_Controller::new_document(QVBoxLayout* widget_container) {

	this->joed_conf = new Joed_Conf();
	this->parser->parse(Joed::Joed_Conf_File, this->joed_conf);

	this->definition_file = new Definitions_File();
	QString file_path = Joed::Base_Definitions_Directory + this->joed_conf->backend_name() +
	                    Joed::Definitions_File_Extension;
	this->parser->parse(file_path, this->definition_file);
	this->backend = this->definition_file->backend();
	this->styles = this->definition_file->styles();

	this->top_block = new Multi_Block(this->styles->find(Style::Document_Key));
	this->top_widget_block = new Multi_Block_Widget(widget_container, this->top_block);
}

void Document_Controller::open(QVBoxLayout* widget_container, QString document_path) {

	// TODO:
	// open document
	// find what is backend and document class
	// load the relevant config
	// load the document blocks
}

void Document_Controller::compile() {
	this->backend->compile(this->top_block->to_backend_code());
}
