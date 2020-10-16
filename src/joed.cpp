#include "joed.h"

void print(QString text) {
	qInfo(text.toUtf8(), true);
}
void print(int number) {
	return print(QString::number(number));
}
