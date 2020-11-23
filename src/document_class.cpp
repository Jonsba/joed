#include "document_class.h"
#include "backend.h"

Document_Class::Document_Class(Class_Objects class_objects) { this->class_objects = class_objects; }

QString Document_Class::name() { return this->the_name; }

void Document_Class::try_load(QString name, Backend* backend) {
	if (name != "") this->the_name = name;
	if (backend != nullptr) this->backend = backend;
	if (this->the_name == "" || this->backend == nullptr) {
		return;
	}
	this->load_class(this->backend->document_class(this->the_name).generic_class,
	                 Joed::Generic_Classes_Path);
	this->load_class(this->backend->document_class(this->the_name).backend_class,
	                 Joed::Backend_Classes_Path + this->backend->name() + Joed::Sep);
}

void Document_Class::load_class(QString the_class, QString folder) {
	int point_pos = 0;
	while (true) {
		point_pos = the_class.indexOf('.', point_pos + 1);
		if (point_pos == -1) {
			break;
		}
		QString base_name = the_class.left(point_pos);
		this->load_class(folder + base_name + File_Extension);
	}
	this->load_class(folder + the_class + File_Extension);
}

void Document_Class::load_class(QString file_path) {
	if (! QFile::exists(file_path)) {
		throw Exception("Cannot load document class '" + this->the_name + "' for backend '" +
		                this->backend->name() + "': " + file_path + " cannot be found");
	}
	Class_File(file_path, this->class_objects);
}
