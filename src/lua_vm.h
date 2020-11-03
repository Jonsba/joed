#ifndef LUA_VM_H
#define LUA_VM_H

#include <QHash>
#include <QString>

char* to_chars(QString text);

class lua_State;

class Lua_VM {
 public:
	Lua_VM();
	int expr_init(QString expr);
	QString expr_exec(int cookie);
	void push_variable(QString variable, QString value);
	void push_variables(QHash<QString, QString> global_dict);

 private:
	void push_scalar(QString key, QString value);
	void push_table(QString key, QString value);
	//
	lua_State* L;
};

#endif // LUA_VM_H
