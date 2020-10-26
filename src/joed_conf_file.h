#ifndef JOED_CONF_FILE_H
#define JOED_CONF_FILE_H

#include "abstract_loadable_file.h"
#include "joed.h"

#include <QString>
#include <QVector>

class Joed_Conf_File : public Abstract_Loadable_File {
 public:
	Joed_Conf_File();
	State process_key(QString key, int level);
	void assign(QString end_key, QString value);
	QString backend_name();
	QString document_class();
	//
	inline static const File_Version Version = {1, 0, 0};
	// inline static const QStringList End_Keys = {Keys[Backend_E], Keys[Document_Class_E]};

 private:
	QString the_backend_name;
	QString the_document_class;
};

#endif // JOED_CONF_FILE_H
