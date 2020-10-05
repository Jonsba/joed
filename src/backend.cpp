#include "src/backend.h"

#include <QDir>
#include <QFile>
#include <QObject>
#include <QProcess>
#include <QTextStream>

Backend::Backend(QProcess *process) {
	this->process = process;
}

void Backend::Compile(QString code) {
	QFile file(TEX_DOCUMENT_PATH);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
	process->setWorkingDirectory(TEX_WORKING_DIRECTORY);
	process->start("/opt/context/tex/texmf-linux-64/bin/context", QStringList() << TEX_DOCUMENT);
}
