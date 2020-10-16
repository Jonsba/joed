#ifndef COMPILER_H
#define COMPILER_H

#include "abstract_buildable_object.h"
#include "joed.h"
#include <QString>
#include <QVector>

class Compile_Env : Abstract_Buildable_Object {
 public:
	Compile_Env();
	virtual void process_intermediate_key(QString key);
	virtual void assign(QString end_key, QString value);
	QString backend_name();
	QString backend_exec();
	//
	inline static const QString Name_Key = "name";
	inline static const QString Exec_Key = "exec";
	inline static const QString_Vector Backend_Keys = {Name_Key, Exec_Key};

 private:
	QString the_backend_name;
	QString the_backend_exec;
};

#endif // COMPILER_H
