#ifndef JOED_CONF_H
#define JOED_CONF_H

#include "abstract_loadable_file.h"
#include "joed.h"

#include <QString>
#include <QVector>

class Joed_Conf : public Abstract_Loadable_File {
 public:
	Joed_Conf();
	State process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value);
	QString backend_name();
	QString document_class();
	//
	inline static const File_Version Version = {1, 0, 0};
	inline static const QString Defaults_Key = "defaults";
	inline static const QString Backend_Key = "backend";
	inline static const QString Document_Class_Key = "document-class";

 private:
	QString the_backend_name;
	QString the_document_class;
};

#endif // JOED_CONF_H
