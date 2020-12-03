#include "document.h"
#include "backend.h"
#include "children_block.h"
#include "document_class.h"
#include "environment.h"
#include "joed_conf_file.h"
#include "layout_entry.h"
#include "lua_client.h"
#include "lua_vm.h"
#include "raw_text_block.h"
#include "root_block.h"
#include "style_properties.h"
#include "styles.h"
#include "text_block.h"
#include "writer.h"

#include <QProcess>

Document::Document(QString document_path) {
	this->the_path = document_path;
	this->lua_vm.reset(new Lua_VM());
	this->the_backend.reset(new Backend(this->lua_vm.get()));
	this->environment.reset(new Environment(this->lua_vm.get()));
	this->styles.reset(new Styles(this->lua_vm.get()));
	this->document_class.reset(new Document_Class({this->environment.get(), this->styles.get()}));

	this->writer.reset(new Writer());
	if (document_path == "") {
		this->create();
		this->the_root_block.reset(new Root_Block(this->styles->find(Field::Key::Document), true));
	} else {
		this->load(document_path);
	}
	this->the_backend->reset_files_info(document_path);
}

Backend* Document::backend() {
	return this->the_backend.get();
}

void Document::create() {
	Joed_Conf_File joed_conf_file;
	joed_conf_file.load(Joed::Joed_Conf_File);
	this->the_backend->load(joed_conf_file.backend_name());
	this->document_class->try_load(joed_conf_file.document_class(), this->the_backend.get());
}

Root_Block* Document::root_block() {
	return this->the_root_block.get();
}

QProcess* Document::compile_process() {
	return this->the_backend->compile_process();
}

void Document::compile() {
	// Order is important because the environment might need to use variables that are set in the
	// blocks (e.g. header and footer)
	this->backend()->write(this->the_root_block->translate(this->backend()->escaper()),
	                       this->the_backend->translated_document()->path);
	this->backend()->write(this->environment->translate(),
	                       this->the_backend->translated_environment()->path);
	this->backend()->compile();
}

QString Document::path() {
	return this->the_path;
}

void Document::save_as(QString file_path) {
	this->the_path = file_path;
	this->save();
}

void Document::save() {
	this->writer->open(this->the_path);
	this->writer->write_pair(Field::Key::Version, this->version_string() + "\n", 0);
	this->writer->write_pair(Field::Key::Backend, this->the_backend->name(), 0);
	this->writer->write_pair(Field::Key::Document_Class, this->document_class->name() + "\n", 0);
	this->root_block()->save(this->writer.get());
	this->writer->close();
	this->the_backend->reset_files_info(this->the_path);
}

void Document::process_intermediate_key(QString key, int level) {
	if (level == 0) {
		if (key == Field::Key::Document) {
			this->the_root_block.reset(
			    new Root_Block(this->styles->find(Field::Key::Document), false));
			this->current_block = this->the_root_block.get();
		} else if (key != Field::Key::Backend && key != Field::Key::Document_Class) {
			throw Exceptions::Invalid_Key();
		}
	} else {
		if (key != Field::Key::Blocks) {
			if (this->parent_blocks[level] == nullptr) {
				throw Exceptions::Invalid_Key();
			}
			Style* style = styles->find(key);
			if (style == nullptr) {
				throw Exception("Cannot find style: " + key);
			}
			switch (style->type) {
			case Style_Type::Children:
				this->current_block = this->parent_blocks[level]->append_child(Styles::Children_Style);
				break;
			case Style_Type::Layouted:
				this->current_block = this->parent_blocks[level]->append_child(style);
				return;
			case Style_Type::Text:
				this->current_block = this->parent_blocks[level]->append_child(style);
				return;
			default:
				throw Exception("Style '" + style->identifier + "' has an unsupported type");
			}
		}
		this->parent_blocks[level + 1] = (Abstract_Multi_Block*)this->current_block;
	}
}

void Document::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	if (end_key == Field::Key::Backend) {
		this->the_backend->load(value);
		this->document_class->try_load("", this->the_backend.get());
	} else if (end_key == Field::Key::Document_Class) {
		this->document_class->try_load(value, nullptr);
	} else if (end_key == Field::Id::Text) {
		if (is_first_value_line) {
			this->current_block = this->parent_blocks[level]->append_child(Styles::Raw_Text_Style);
		}
		((Raw_Text_Block*)this->current_block)->add_loaded_text(value);
	} else {
		throw Exceptions::Invalid_Key();
	}
}

Document::~Document() = default;
