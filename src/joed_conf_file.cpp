#include "joed_conf_file.h"

Joed_Conf_File::Joed_Conf_File() : Abstract_Loadable_File(Version) {}

Parse_State Joed_Conf_File::process_key(QString key, int level) {
	if (key != Joed::Keys[Defaults_E]) {
		return Parse_State::Invalid_Key_E;
	}
	return Parse_State::Success_E;
}

Parse_State Joed_Conf_File::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Joed::Keys[Backend_E]) {
		this->the_backend_name = value;
	} else if (end_key == Joed::Keys[Document_Class_E]) {
		this->the_document_class = value;
	} else {
		return Parse_State::Invalid_Key_E;
	}
	return Parse_State::Success_E;
}

QString Joed_Conf_File::backend_name() {
	return this->the_backend_name;
}
QString Joed_Conf_File::document_class() {
	return this->the_document_class;
}
