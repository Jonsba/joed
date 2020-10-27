#ifndef LUA_CLIENT_H
#define LUA_CLIENT_H

#include <QHash>

class Lua_VM;

class Lua_Client {
 public:
	Lua_Client(Lua_VM* lua_vm);
	QString eval(QString expr);
	QString eval(QString expr, QHash<QString, QString> global_dict);

 private:
	Lua_VM* lua_vm;
	int lua_cookie;
};

#endif // LUA_CLIENT_H
