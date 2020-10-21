#ifndef DEFINITION_FILE_H
#define DEFINITION_FILE_H

#include "abstract_loadable_file.h"
#include "joed.h"
#include <QHash>
#include <QString>
#include <QVector>

class Joed_Conf_File;
class Styles;
class Backend;

class Definitions_File : public Abstract_Loadable_File {
 public:
	Definitions_File();
	State process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value);
	Styles* styles();
	Backend* backend();
	//
	inline static const File_Version Version = {1, 0, 0};
	const QString Backend_Key = "backend";
	const QString Styles_Key = "styles";

 private:
	QHash<QString, Abstract_Loadable_Object*> objects_table;
	Abstract_Loadable_Object* current_object;
	QString top_key;
	QString current_key;
};

#endif // DEFINITION_FILE_H
