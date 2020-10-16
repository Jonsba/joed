#include "src/frontend/editor.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Editor e;
	e.show();
	return a.exec();
}
