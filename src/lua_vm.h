#ifndef LUA_VM_H
#define LUA_VM_H

#include <QString>

char* To_Chars(QString text);

class lua_State;

class Lua_VM {
 public:
	Lua_VM();
	int expr_init(QString expr);
	QString expr_exec(int cookie);
	void set_global_variable(QString key, QString value);

 private:
	//
	lua_State* L;
};

#endif // LUA_VM_H
