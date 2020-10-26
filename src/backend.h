#ifndef BACKEND_H
#define BACKEND_H

#include "abstract_loadable_tree.h"
#include "joed.h"
#include <QString>
#include <QVector>

#define DOCUMENT_NAME "document"
#define TEX_DOCUMENT DOCUMENT_NAME ".tex"
#define TEX_WORKING_DIRECTORY "/home/jonas-travail/Documents/github/joed/build/tex/"
#define TEX_DOCUMENT_PATH TEX_WORKING_DIRECTORY TEX_DOCUMENT
#define PDF_DOCUMENT_PATH TEX_WORKING_DIRECTORY DOCUMENT_NAME ".pdf"

class QProcess;

class Backend : public Abstract_Loadable_Tree {
 public:
	Backend();
	State process_key(QString key, int level);
	void assign(QString end_key, QString value);
	QProcess* compile_process();
	void compile(QString code);
	//
	// inline static const QStringList End_Keys = {Keys[Name_E], Keys[Exec_E]};

 private:
	QString name;
	QString exec;
	QProcess* the_compile_process;
};

#endif // BACKEND_H
