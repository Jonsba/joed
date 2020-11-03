#ifndef LUA_CLIENT_H
#define LUA_CLIENT_H

#include <QHash>

class Lua_VM;

class Lua_Client {
 public:
	Lua_Client(Lua_VM* lua_vm);
	void add_output_line(QString line, bool reset);
	QString eval();
	QString eval(QHash<QString, QString> global_dict);
	//
	static inline const QString Newline = "'\\n\\n'";

 private:
	Lua_VM* lua_vm;
	QString output;
	int lua_cookie;
};

#endif // LUA_CLIENT_H
