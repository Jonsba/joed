#ifndef LUA_VM_H
#define LUA_VM_H

#include <QString>

char* To_Chars(QString text);

class lua_State;

class Lua_VM {
 public:
	Lua_VM();
	int Expr_Init(QString expr);
	QString Expr_Exec(int cookie);
	void Set_Global_Variable(QString key, QString value);

 private:
	//
	lua_State* L;
};

#endif // LUA_VM_H
