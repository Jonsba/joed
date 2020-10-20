#ifndef COMPILER_H
#define COMPILER_H

#include "abstract_loadable_object.h"
#include "joed.h"
#include <QString>
#include <QVector>

#define DOCUMENT_NAME "document"
#define TEX_DOCUMENT DOCUMENT_NAME ".tex"
#define TEX_WORKING_DIRECTORY "/home/jonas-travail/Documents/github/joed/build/tex/"
#define TEX_DOCUMENT_PATH TEX_WORKING_DIRECTORY TEX_DOCUMENT
#define PDF_DOCUMENT_PATH TEX_WORKING_DIRECTORY DOCUMENT_NAME ".pdf"

class QProcess;

class Backend : public Abstract_Loadable_Object {
 public:
	Backend();
	State process_intermediate_key(QString key, int level);
	void assign(QString end_key, QString value);
	void set_compile_process(QProcess* compile_process);
	void compile(QString code);
	//
	inline static const QString Name_Key = "name";
	inline static const QString Exec_Key = "exec";

 private:
	QString name;
	QString exec;
	QProcess* compile_process;
};

#endif // COMPILER_H
