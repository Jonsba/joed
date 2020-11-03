#include "document.h"
#include "backend.h"
#include "children_block.h"
#include "definitions_loader.h"
#include "environment.h"
#include "joed_conf_file.h"
#include "lua_vm.h"
#include "raw_text_block.h"
#include "style.h"
#include "styles.h"
#include "text_block.h"
#include "top_block.h"

Document::Document(QString document_path) : Abstract_Loadable_File(Version) {
	this->lua_vm = new Lua_VM();
	if (document_path == "") {
		this->create();
		this->the_root_block = new Top_Block(this->styles->find(Keys[Document_E]), false);
	} else {
		this->open(document_path);
	}
}

void Document::add_block(Abstract_Block* new_block) {
	Layout_Block* parent_block = (Layout_Block*)this->current_blocks[this->block_level - 1];
	parent_block->add_block(new_block);
	this->current_blocks[this->block_level] = new_block;
}

State Document::process_key(QString key, int level) {
	if (level == 0) {
		if (key != Keys[Content_E]) {
			return State::Parsing_Value;
		}
		this->the_root_block = new Top_Block(this->styles->find(Keys[Document_E]));
		this->current_blocks[0] = this->the_root_block;
	}
	if (Blocks_Keys.contains(key)) {
		// Every 3 levels, there is a offset of 1 level to be corrected
		this->block_level = level - level / 3;
		if (key == Keys[Children_E]) {
			this->add_block(new Children_Block());
		}
		return State::Parsing_Key;
	} else if (End_Keys.contains(key)) {
		return State::Parsing_Value;
	}
	return State::Parsing_Key;
}

void Document::assign(QString end_key, QString value, bool is_first_value_line) {
	static QString backend_name = "";
	if (end_key == Keys[Backend_E]) {
		backend_name = value;
	} else if (end_key == Keys[Document_Class_E]) {
		this->create(backend_name, value);
	} else if (end_key == Keys[Style_E]) {
		Style* style = this->styles->find(value);
		switch (style->type()) {
		case Block_Type::Layout_Block_E: {
			this->add_block(new Layout_Block(style));
			break;
		}
		case Block_Type::Text_Block_E:
			this->add_block(new Text_Block(style));
			break;
		default:
			error("Not implemented");
		}
	} else if (end_key == Keys[Text_E]) {
		Text_Block* current_block = (Text_Block*)this->current_blocks[this->block_level];
		current_block->add_block(new Raw_Text_Block(value));
	}
}

Backend* Document::backend() {
	return this->the_backend;
}

void Document::create() {
	Joed_Conf_File* joed_conf_file = new Joed_Conf_File();
	joed_conf_file->load(Joed::Joed_Conf_File);
	this->create(joed_conf_file->backend_name(), joed_conf_file->document_class());
}

void Document::create(QString backend_name, QString document_class) {
	Definitions_Loader* definition_file =
	    new Definitions_Loader(this->lua_vm, backend_name, document_class);
	this->the_backend = definition_file->backend();
	this->styles = definition_file->styles();
	this->environment = definition_file->environment();
}

void Document::open(QString document_path) {
	this->load(document_path);
}

Top_Block* Document::root_block() {
	return this->the_root_block;
}

QProcess* Document::compile_process() {
	return this->the_backend->compile_process();
}

void Document::compile() {
	this->the_backend->compile(this->the_root_block->translate(), this->environment->translate());
}
