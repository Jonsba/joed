#include "joed_conf.h"

Joed_Conf::Joed_Conf() {}

State Joed_Conf::process_intermediate_key(QString key, int level) {
	if (key == Defaults_Key) {
		return Parsing_Key;
	}
	return Parsing_Value;
}

void Joed_Conf::assign(QString end_key, QString value) {
	if (end_key == Backend_Key) {
		this->the_backend_name = value;
	} else if (end_key == Document_Class_Key) {
		this->the_document_class = value;
	} else {
		error("Unknown joed-conf key: " + end_key + " = " + value);
	}
}

QString Joed_Conf::backend_name() {
	return this->the_backend_name;
}
QString Joed_Conf::document_class() {
	return this->the_document_class;
}
