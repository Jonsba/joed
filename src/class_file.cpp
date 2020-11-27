#include "class_file.h"
#include "environment.h"
#include "styles.h"

Class_File::Class_File(QString path, Class_Objects class_objects) {
	this->objects_table[Field::Key::Document] = class_objects.document_styles;
	this->objects_table[Field::Key::Environment] = class_objects.environment;
	this->load(path);
};

void Class_File::process_intermediate_key(QString key, int level) {
	if (level == 0) {
		this->current_object = this->objects_table[key];
		if (this->current_object == nullptr) {
			throw Exceptions::Invalid_Key();
		}
	} else {
		((Abstract_Loadable_Tree*)this->current_object)->process_intermediate_key(key, level);
	}
}

void Class_File::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	this->current_object->assign(end_key, value, level, is_first_value_line);
}
