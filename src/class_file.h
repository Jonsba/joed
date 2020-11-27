#ifndef CLASS_FILE_H
#define CLASS_FILE_H

#include "abstract_loadable_file.h"
#include "joed.h"

#include <QHash>
#include <QString>

class Lua_VM;
class Styles;
class Environment;

struct Class_Objects {
	Environment* environment;
	Styles* document_styles;
};

// Represents a generic or a backend class file
class Class_File final : public Abstract_Loadable_File {
 public:
	Class_File(QString path, Class_Objects class_objects);

 protected:
	const File_Version Version() { return {0, 1, 0}; }
	void process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value, int level, bool is_first_value_line);

 private:
	QHash<QString, Abstract_Loadable_Object*> objects_table;
	Abstract_Loadable_Object* current_object;
};

#endif // CLASS_FILE_H
