#include "definitions_loader.h"
#include "backend.h"
#include "environment.h"
#include "style.h"
#include "styles.h"

Definitions_Loader::Definitions_Loader(Lua_VM* lua_vm, QString backend_name, QString document_class)
    : Abstract_Loadable_File(Version) {
	this->objects_table[Joed::Keys[Styles_E]] = new Styles(lua_vm);
	this->objects_table[Joed::Keys[Backend_E]] = new Backend(lua_vm, backend_name, document_class);
	this->load(Joed::Base_Definitions_Directory + backend_name + "/base" +
	           Joed::Definitions_File_Extension);
	this->objects_table[Joed::Keys[Environment_E]] = new Environment(lua_vm);
	this->load(Joed::Base_Definitions_Directory + backend_name + "/" + document_class +
	           Joed::Definitions_File_Extension);
}

State Definitions_Loader::process_key(QString key, int level) {
	if (level == 0) {
		this->current_object = this->objects_table[key];
		return State::Parsing_Key;
	} else {
		return this->current_object->process_key(key, level);
	}
}

void Definitions_Loader::assign(QString end_key, QString value, bool is_first_value_line) {
	this->current_object->assign(end_key, value, is_first_value_line);
}

Backend* Definitions_Loader::backend() {
	return (Backend*)this->objects_table[Joed::Keys[Backend_E]];
}

Styles* Definitions_Loader::styles() {
	return (Styles*)this->objects_table[Joed::Keys[Styles_E]];
}

Environment* Definitions_Loader::environment() {
	return (Environment*)this->objects_table[Joed::Keys[Environment_E]];
}
