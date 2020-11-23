#include "joed_conf_file.h"

Joed_Conf_File::Joed_Conf_File() {}

void Joed_Conf_File::process_intermediate_key(QString key, int level) {
	if (key != Field::Key::Defaults) {
		throw Invalid_Key_Exception();
	}
}

void Joed_Conf_File::assign(QString end_key, QString value, int level, bool is_first_value_line) {
	if (end_key == Field::Key::Backend) {
		this->the_backend_name = value;
	} else if (end_key == Field::Key::Document_Class) {
		this->the_document_class = value;
	} else {
		throw Invalid_Key_Exception();
	}
}

QString Joed_Conf_File::backend_name() { return this->the_backend_name; }
QString Joed_Conf_File::document_class() { return this->the_document_class; }
