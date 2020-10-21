#include "definitions_file.h"
#include "backend.h"
#include "style.h"
#include "styles.h"

Definitions_File::Definitions_File() : Abstract_Loadable_File(Version) {
	this->objects_table[Styles_Key] = new Styles();
	this->objects_table[Backend_Key] = new Backend();
}

State Definitions_File::process_intermediate_key(QString key, int level) {
	if (level == 0) {
		this->current_object = this->objects_table[key];
		if (this->current_object == nullptr) {
			error("Unknown top level key: " + key);
		}
		return Parsing_Key;
	} else {
		return this->current_object->process_intermediate_key(key, level);
	}
}

void Definitions_File::assign(QString key, QString value) {
	this->current_object->assign(key, value);
}

Styles* Definitions_File::styles() {
	return (Styles*)this->objects_table[Styles_Key];
}
Backend* Definitions_File::backend() {

	return (Backend*)this->objects_table[Backend_Key];
}
