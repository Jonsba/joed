#ifndef LUA_VM_H
#define LUA_VM_H

#include <QHash>
#include <QString>

typedef QHash<QString, QString> Global_Dict;

char* To_Chars(QString text);

class lua_State;

class Lua_VM {
 public:
	Lua_VM();
	int expr_init(QString expr);
	QString expr_exec(int cookie);
	void set_global_variable(QString key, QString value);
	void set_global_variables(Global_Dict global_dict);

 private:
	//
	lua_State* L;
};

#endif // LUA_VM_H
