#include "src/backend.h"
#include "src/frontend/editor.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	Backend b;
	Editor w(&b);
	w.show();
	return a.exec();
}
