#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "abstract_loadable_tree.h"
#include <QString>

class Lua_VM;
class Lua_Client;

class Environment : public Abstract_Loadable_Tree {
 public:
	Environment(Lua_VM* lua_vm);
	State process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);
	QString translate();
	//
	inline static const QString Name_Id = "environment.name";
	inline static const QString Basename_Id = "document-environment";

 private:
	Lua_Client* lua_client;
	QString name;
};

#endif // ENVIRONMENT_H
