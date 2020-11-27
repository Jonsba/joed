#ifndef ESCAPER_H
#define ESCAPER_H

#include <QLinkedList>
#include <QScopedPointer>
#include <QString>

class Lua_VM;
class Lua_Client;

class Escaper {
 public:
	Escaper(Lua_VM* lua_vm);
	~Escaper();
	void parse(QString escape_spec_line);
	QString escape(QString text);

 private:
	QLinkedList<QStringList> escape_table;
	QScopedPointer<Lua_Client> lua_client;
};

#endif // ESCAPER_H
