#include "document.h"
#include "backend.h"
#include "children_block.h"
#include "definitions_file.h"
#include "environment.h"
#include "escaper.h"
#include "joed_conf_file.h"
#include "layout_entry.h"
#include "lua_client.h"
#include "lua_vm.h"
#include "raw_text_block.h"
#include "root_block.h"
#include "style.h"
#include "styles.h"
#include "text_block.h"
#include "writer.h"

#include <QProcess>

Document::Document(QString document_path) : Abstract_Loadable_File(Version) {
	this->the_path = document_path;
	this->lua_vm.reset(new Lua_VM());
	this->styles.reset(new Styles(this->lua_vm.get()));
	this->the_backend.reset(new Backend(this->lua_vm.get()));
	this->environment.reset(new Environment(this->lua_vm.get()));
	this->writer.reset(new Writer());
	if (document_path == "") {
		this->create();
		this->the_root_block.reset(new Root_Block(this->styles->find(Field::Key::Document),
		                                          this->the_backend->escaper(), true));
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
	this->backend_definitions_file.reset(new Definitions_File(
	    joed_conf_file.backend_name(),
	    {this->the_backend.get(), this->environment.get(), this->styles.get()}));

	this->document_class_definitions_file.reset(
	    new Definitions_File(joed_conf_file.document_class(),
	                         {this->the_backend.get(), this->environment.get(), this->styles.get()},
	                         this->backend_definitions_file.get()));
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
	this->backend()->write(this->the_root_block->translate(),
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
	this->writer->write_pair(Field::Key::Backend, this->backend_definitions_file->info()->name, 0);
	this->writer->write_pair(Field::Key::Document_Class,
	                         this->document_class_definitions_file->info()->name + "\n", 0);
	this->root_block()->save(this->writer.get());
	this->writer->close();
	this->the_backend->reset_files_info(this->the_path);
}

Parse_State Document::process_key(QString key, int level) {
	if (level == 0) {
		if (key == Field::Key::Content) {
			this->the_root_block.reset(new Root_Block(this->styles->find(Field::Key::Document),
			                                          this->the_backend->escaper(), false));
			this->current_blocks[0] = this->the_root_block.get();
		} else if (key != Field::Key::Backend && key != Field::Key::Document_Class) {
			return Parse_State::Invalid_Key_E;
		}
	}
	if (Blocks_Keys.contains(key)) {
		// Every 3 levels, there is a offset of 1 level to be corrected
		this->block_level = level - level / 3;
		this->current_parent_block = (Layout_Block*)this->current_blocks[this->block_level - 1];
		if (key == Field::Key::Children) {
			this->current_blocks[this->block_level] =
			    this->current_parent_block->create_block(Abstract_Block::Children_Block_Type);
		}
	} else if (key != Field::Key::Content) {
		return Parse_State::Invalid_Key_E;
	}
	return Parse_State::Success_E;
}

Parse_State Document::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Field::Key::Backend) {
		this->backend_definitions_file.reset(new Definitions_File(
		    value, {this->the_backend.get(), this->environment.get(), this->styles.get()}));
	} else if (end_key == Field::Key::Document_Class) {
		this->document_class_definitions_file.reset(new Definitions_File(
		    value, {this->the_backend.get(), this->environment.get(), this->styles.get()},
		    this->backend_definitions_file.get()));
	} else if (end_key == Field::Key::Style) {
		Style* style = this->styles->find(value);
		switch (style->type().base) {
		case Block_Base_Type::Layout_Block_E: {
			this->current_blocks[this->block_level] = this->current_parent_block->create_block(style);
			break;
		}
		case Block_Base_Type::Text_Block_E:
			this->current_blocks[this->block_level] =
			    this->current_parent_block->create_block(style, this->the_backend->escaper());
			break;
		default:
			return Parse_State::Invalid_Value_E;
		}
	} else if (end_key == Field::Key::Text) {
		Text_Block* text_block = (Text_Block*)this->current_blocks[this->block_level];
		text_block->add_loaded_text(value, is_first_value_line);
	} else {
		return Parse_State::Invalid_Key_E;
	}
	return Parse_State::Success_E;
}

Document::~Document() = default;
