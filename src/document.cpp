#include "document.h"
#include "backend.h"
#include "definitions_parser.h"
#include "frontend/multi_block_widget.h"
#include "initializer.h"
#include "joed.h"
#include "multi_block.h"
#include "style.h"
#include "styles.h"

#include <QProcess>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>

Document::Document(QVBoxLayout* widget_container, QProcess* compile_process) {
	this->styles_initializer = new Initializer<Styles>(Style::Intermediate_Keys, Style::End_Keys);
	this->backend_initializer = new Initializer<Backend>({}, Backend::Backend_Keys);
	Definitions_Parser(this->styles_initializer, this->backend_initializer);
	this->styles = this->styles_initializer->loaded_object();
	this->backend = this->backend_initializer->loaded_object();
	this->backend->set_compile_process(compile_process);
	//
	this->top_block = new Multi_Block(this->styles->find(Style::Document_Key));
	this->top_widget_block = new Multi_Block_Widget(widget_container, this->top_block);
}

void Document::compile() {
	this->backend->compile(this->top_block->to_backend_code());
}
