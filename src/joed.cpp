#include "joed.h"

void error(QString error_msg) {
	echo(error_msg);
	throw;
}

void echo(QString text) {
	qInfo(text.toUtf8(), true);
}
void echo(int number) {
	return echo(QString::number(number));
}
