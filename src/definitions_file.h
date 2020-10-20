#ifndef DEFINITION_FILE_H
#define DEFINITION_FILE_H

#include "abstract_versioned_loadable_object.h"
#include "joed.h"
#include <QHash>
#include <QString>
#include <QVector>

class Joed_Conf;
class Styles;
class Backend;

class Definitions_File : public Abstract_Versioned_Loadable_Object {
 public:
	Definitions_File();
	State process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value);
	Styles* styles();
	Backend* backend();
	//
	inline static const File_Version Version = {1, 1, 1};
	const QString Version_Key = "format-version";
	const QString Backend_Key = "backend";
	const QString Styles_Key = "styles";

 private:
	QHash<QString, Abstract_Loadable_Object*> objects_table;
	Abstract_Loadable_Object* current_object;
	QString top_key;
	QString current_key;
};

#endif // DEFINITION_FILE_H
