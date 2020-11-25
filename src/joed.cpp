#include "joed.h"

void echo(QString text) {
	qInfo(text.toUtf8(), true);
}
void echo(int number) {
	return echo(QString::number(number));
}
