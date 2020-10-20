#include "src/frontend/editor.h"

#include "joed.h"
#include <QApplication>
#include <QChar>
#include <QString>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	QString document_path = "";
	if (argc == 2) {
		document_path = QString(argv[1]);
	}
	Editor e(document_path);
	e.show();
	return a.exec();
}
