#include "definitions_file.h"
#include "backend.h"
#include "style.h"
#include "styles.h"

Definitions_File::Definitions_File(QString backend_name, Lua_VM* lua_vm)
    : Abstract_Loadable_File(Version) {
	this->objects_table[Keys[Styles_E]] = new Styles(lua_vm);
	this->objects_table[Keys[Backend_E]] = new Backend(lua_vm);
	this->load(Joed::Base_Definitions_Directory + backend_name + Joed::Definitions_File_Extension);
}

State Definitions_File::process_key(QString key, int level) {
	if (level == 0) {
		this->current_object = this->objects_table[key];
		return State::Parsing_Key;
	} else {
		return this->current_object->process_key(key, level);
	}
}

void Definitions_File::assign(QString end_key, QString value) {
	this->current_object->assign(end_key, value);
}

Styles* Definitions_File::styles() {
	return (Styles*)this->objects_table[Keys[Styles_E]];
}
Backend* Definitions_File::backend() {

	return (Backend*)this->objects_table[Keys[Backend_E]];
}
