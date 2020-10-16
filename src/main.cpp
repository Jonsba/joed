#include "src/frontend/editor.h"

#include "joed.h"
#include <QApplication>
#include <QChar>
#include <QString>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Editor e;
	e.show();
	return a.exec();
}
