#include "editor.h"
#include "ui_editor.h"

#include <QTabWidget>
#include <QTextEdit>
#include <poppler-qt5.h>

Editor::Editor(Backend *backend, QWidget *parent) : QMainWindow(parent), ui(new Ui::Editor) {
	ui->setupUi(this);
	this->backend = backend;
	ui->Backend_Code_Block->setFocus();
	QObject::connect(ui->Mode_Tab, &QTabWidget::currentChanged, this, &Editor::Compile);
}

void Editor::Compile() {
	if (ui->Mode_Tab->currentIndex() == 1) {
		this->backend->Compile(ui->Backend_Code_Block->toPlainText());
	}
}

Editor::~Editor() {
	delete ui;
}
