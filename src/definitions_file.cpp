#include "definitions_file.h"
#include "abstract_loadable_tree.h"
#include "backend.h"
#include "document_styles.h"
#include "environment.h"

Definitions_File::Definitions_File(QString name, Definitions_Objects definitions_object,
                                   Definitions_File* parent)
    : Abstract_Loadable_File(Version) {

	this->objects_table[Field::Key::Document_Styles] = definitions_object.document_styles;
	this->objects_table[Field::Key::Backend] = definitions_object.backend;
	this->objects_table[Field::Key::Environment] = definitions_object.environment;

	if (parent == nullptr) {
		this->base_path = Root_Directory + name + Joed::Sep + name;
	} else {
		this->base_path = parent->base_path + "." + name;
	}
	this->the_file_info = {name, this->base_path + File_Extension};
	this->load(this->the_file_info.path);
}

Definitions_Info* Definitions_File::info() {
	return &this->the_file_info;
}

void Definitions_File::process_key(QString key, int level) {
	if (level == 0) {
		this->current_object = this->objects_table[key];
		if (this->current_object == nullptr) {
			throw Invalid_Key_Exception();
		}
	} else {
		((Abstract_Loadable_Tree*)this->current_object)->process_key(key, level);
	}
}

void Definitions_File::assign(QString end_key, QString value, bool is_first_value_line) {
	this->current_object->assign(end_key, value, is_first_value_line);
}
