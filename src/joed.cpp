#include "joed.h"

void error(QString error_msg) {
	print(error_msg);
	throw;
}

void print(QString text) {
	qInfo(text.toUtf8(), true);
}
void print(int number) {
	return print(QString::number(number));
}
