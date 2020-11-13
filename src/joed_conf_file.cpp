#include "joed_conf_file.h"

Joed_Conf_File::Joed_Conf_File() : Abstract_Loadable_File(Version) {}

// At the moment, one possible key (defaults), so we do nothing
void Joed_Conf_File::process_key(QString key, int level) {}

void Joed_Conf_File::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Joed::Keys[Backend_E]) {
		this->the_backend_name = value;
	} else if (end_key == Joed::Keys[Document_Class_E]) {
		this->the_document_class = value;
	}
}

QString Joed_Conf_File::backend_name() {
	return this->the_backend_name;
}
QString Joed_Conf_File::document_class() {
	return this->the_document_class;
}
