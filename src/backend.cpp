#include "backend.h"
#include "joed.h"
#include "layout_block.h"
#include "style.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>

Backend::Backend() {
	this->the_compile_process = new QProcess();
}

State Backend::process_key(QString key, int level) {
	return State::Parsing_Value;
}

void Backend::assign(QString end_key, QString value) {
	if (end_key == Keys[Name_E]) {
		this->name = value;
	} else if (end_key == Keys[Exec_E]) {
		this->exec = value;
	}
}

QProcess* Backend::compile_process() {
	return this->the_compile_process;
}

void Backend::compile(QString code) {
	QFile file(TEX_DOCUMENT_PATH);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
	this->the_compile_process->setWorkingDirectory(TEX_WORKING_DIRECTORY);
	this->the_compile_process->start(this->exec, QStringList() << TEX_DOCUMENT);
}
