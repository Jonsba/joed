#ifndef DEFINITIONS_LOADER_H
#define DEFINITIONS_LOADER_H

#include "abstract_loadable_file.h"
#include "joed.h"
#include <QHash>
#include <QString>
#include <QVector>

class Lua_VM;
class Joed_Conf_File;
class Styles;
class Backend;
class Environment;

class Definitions_Loader : public Abstract_Loadable_File {
 public:
	Definitions_Loader(Lua_VM* lua_vm, QString backend_name, QString document_class);
	State process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);
	Styles* styles();
	Backend* backend();
	Environment* environment();
	//
	inline static const File_Version Version = {1, 0, 0};

 private:
	QHash<QString, Abstract_Loadable_Tree*> objects_table;
	Abstract_Loadable_Tree* current_object;
};

#endif // DEFINITIONS_LOADER_H
