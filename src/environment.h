#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "abstract_loadable_tree.h"

#include <QScopedPointer>
#include <QString>

class Lua_VM;
class Lua_Client;

class Environment final : public Abstract_Loadable_Object {
 public:
	Environment(Lua_VM* lua_vm);
	~Environment();
	QString translate();
	//
	inline static const QString Name_Id = "document-environment";

 protected:
	void assign(QString end_key, QString value, bool is_first_value_line);

 private:
	QScopedPointer<Lua_Client> lua_client;
	QString name;
};

#endif // ENVIRONMENT_H
