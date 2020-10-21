#include "document.h"
#include "backend.h"
#include "definitions_file.h"
#include "joed_conf_file.h"
#include "multi_block.h"
#include "style.h"
#include "styles.h"

Document::Document(QString document_path) : Abstract_Loadable_File(Version) {
	if (document_path == "") {
		this->create();
	} else {
		this->open(document_path);
	}
	this->the_root_block = new Multi_Block(this->styles->find(Style::Document_Key));
}

State Document::process_intermediate_key(QString key, int level) {
	if (level == 1) {
	}
	return Parsing_Key;
}

void Document::assign(QString key, QString value) {}

void Document::create() {

	this->joed_conf = new Joed_Conf_File();
	this->joed_conf->load(Joed::Joed_Conf_File);

	this->definition_file = new Definitions_File();
	this->definition_file->load(Joed::Base_Definitions_Directory + this->joed_conf->backend_name() +
	                            Joed::Definitions_File_Extension);
	this->backend = this->definition_file->backend();
	this->styles = this->definition_file->styles();
}

void Document::open(QString document_path) {

	// TODO:
	// open document
	// find what is backend and document class
	// load the relevant config
	// load the document blocks
	// this->document = new Document(this->styles);
}

Multi_Block* Document::root_block() {
	return this->the_root_block;
}

QProcess* Document::compile_process() {
	return this->backend->compile_process();
}

void Document::compile() {
	this->backend->compile(this->the_root_block->to_backend_code());
}
