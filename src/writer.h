#ifndef WRITER_H
#define WRITER_H

#include "abstract_loadable_file.h"
#include <QFile>

class Writer {
 public:
	Writer();
	void open(QString file_path);
	void close();
	void write_key(QString key, int level);
	void write_end_key(QString end_key, int level);
	void write_value(QString value, int level, QString escape_char = "");
	void write_pair(QString end_key, QString value, int level);

 private:
	void write_line(QString line, int level);
	void write_tabulations(int level);
	//
	QFile file_descr;
};

#endif // WRITER_H
