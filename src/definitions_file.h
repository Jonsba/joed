#ifndef DEFINITIONS_FILE_H
#define DEFINITIONS_FILE_H

#include "abstract_loadable_file.h"
#include "joed.h"
#include <QHash>
#include <QString>
#include <QVector>

class Lua_VM;
class Joed_Conf_File;
class Styles;
class Backend;

class Definitions_File : public Abstract_Loadable_File {
 public:
	Definitions_File(QString backend_name, Lua_VM* lua_vm);
	State process_key(QString key, int level);
	void assign(QString end_key, QString value);
	Styles* styles();
	Backend* backend();
	//
	inline static const File_Version Version = {1, 0, 0};
	// inline static const QStringList Keys_Values = {Keys[Backend_E], Keys[Styles_E]};

 private:
	QHash<QString, Abstract_Loadable_Tree*> objects_table;
	Abstract_Loadable_Tree* current_object;
};

#endif // DEFINITIONS_FILE_H
