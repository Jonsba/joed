#ifndef DOCUMENT_CLASS_H
#define DOCUMENT_CLASS_H

#include "class_file.h"

class Backend;

class Document_Class {
 public:
	Document_Class(Class_Objects class_objects);
	void try_load(QString name, Backend* backend);
	QString name();

 protected:
	void process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);

 private:
	void load_class(QString the_class, QString parent_folder);
	void load_class(QString file_path);
	//
	inline static const QString File_Extension = ".cls";
	//
	QString the_name;
	Backend* backend;
	Class_Objects class_objects;
};

#endif // DOCUMENT_CLASS_H
