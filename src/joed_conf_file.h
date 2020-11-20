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

 protected:
	const File_Version Version() { return {0, 0, 0}; }
	void process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);

 private:
	QString the_backend_name;
	QString the_document_class;
};

#endif // JOED_CONF_FILE_H
