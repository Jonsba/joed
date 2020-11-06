#include "writer.h"
#include "joed.h"

Writer::Writer() {}

void Writer::open(QString file_path) {
	this->file_descr.setFileName(file_path);
	if (! this->file_descr.open(QIODevice::WriteOnly | QIODevice::Text)) {
		error("Cannot open " + file_path + " for writing");
		return;
	}
}

void Writer::write_key(QString key, int level) {
	this->write_tabulations(level);
	this->file_descr.write(key.toUtf8() + ":\n");
}

void Writer::write_value(QString value, int level) {
	this->write_tabulations(level);
	this->file_descr.write(value.toUtf8() + '\n');
}

void Writer::write_pair(QString key, QString value, int level) {
	this->write_tabulations(level);
	this->file_descr.write(key.toUtf8() + ": " + value.toUtf8() + "\n");
}

void Writer::close() {
	this->file_descr.close();
}

void Writer::write_tabulations(int level) {
	QString tabulations = "";
	for (int i = 0; i < level; i++) {
		tabulations += '\t';
	}
	this->file_descr.write(tabulations.toUtf8());
}
