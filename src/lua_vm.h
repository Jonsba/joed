#ifndef LUA_VM_H
#define LUA_VM_H

#include <QHash>
#include <QString>

char* to_chars(QString text);

class lua_State;

class Lua_VM {
 public:
	Lua_VM();
	int load_expr(QString expr);
	QString eval_expr(int cookie);
	void push_variable(QString variable, QString value);
	void push_variables(QHash<QString, QString> global_dict);
	lua_State* L();

 private:
	void push_scalar(QString key, QString value);
	void push_table(QString key, QString value);
	//
	lua_State* the_L;
};

#endif // LUA_VM_H
