#ifndef LUA_CLIENT_H
#define LUA_CLIENT_H

#include <QHash>
#include <QStringList>

class Lua_VM;

class Lua_Client {
 public:
	Lua_Client(Lua_VM* lua_vm);
	void add_expr_line(QString line, bool reset);
	QString eval_expr();
	QString eval_expr(QHash<QString, QString> global_dict);
	QStringList eval_inline_array_expr(QString array_expr, int array_size);
	//
	static inline const QString Newline = "'\\n'";

 private:
	Lua_VM* lua_vm;
	QString expr;
	int lua_cookie;
};

#endif // LUA_CLIENT_H
