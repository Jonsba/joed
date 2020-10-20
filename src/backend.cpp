#include "backend.h"
#include "joed.h"
#include "multi_block.h"
#include "style.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>

Backend::Backend() {}

State Backend::process_intermediate_key(QString key, int level) {
	return Parsing_Value;
}

void Backend::assign(QString end_key, QString value) {
	if (end_key == Name_Key) {
		this->name = value;
	} else if (end_key == Exec_Key) {
		this->exec = value;
	} else {
		error("Unknown backend key: " + end_key + " = " + value);
	}
}

void Backend::set_compile_process(QProcess* compile_process) {
	this->compile_process = compile_process;
}

void Backend::compile(QString code) {
	QFile file(TEX_DOCUMENT_PATH);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
	compile_process->setWorkingDirectory(TEX_WORKING_DIRECTORY);
	compile_process->start(this->exec, QStringList() << TEX_DOCUMENT);
}
