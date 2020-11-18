#ifndef JOED_CONF_FILE_H
#define JOED_CONF_FILE_H

#include "abstract_loadable_file.h"
#include "joed.h"

#include <QString>
#include <QVector>

class Joed_Conf_File : public Abstract_Loadable_File {
 public:
	Joed_Conf_File();
	QString backend_name();
	QString document_class();
	//
 protected:
	Parse_State process_key(QString key, int level);
	Parse_State assign(QString end_key, QString value, bool is_first_value_line);
	inline static const File_Version Version = {0, 0, 0};

 private:
	QString the_backend_name;
	QString the_document_class;
};

#endif // JOED_CONF_FILE_H
