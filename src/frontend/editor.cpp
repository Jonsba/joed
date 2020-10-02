#include "editor.h"
#include "ui_editor.h"

#include <QLabel>
#include <QTabWidget>
#include <QTextEdit>

Editor::Editor(QWidget *parent) : QMainWindow(parent), ui(new Ui::Editor) {
	ui->setupUi(this);
	ui->Backend_Code_Block->setFocus();
	this->compilation_process = new QProcess();
	this->backend = new Backend(this->compilation_process);
	this->pdf_viewer = new PDF_Viewer(ui->View_Mode_Tab);
	ui->View_Mode_Layout->addWidget(this->pdf_viewer);
	this->text_changed = true;
	QObject::connect(ui->Backend_Code_Block, &QTextEdit::textChanged, this, &Editor::Text_Changed);
	QObject::connect(ui->Mode_Tab, &QTabWidget::currentChanged, this, &Editor::Compile_When_Needed);
	QObject::connect(this->compilation_process, qOverload<int>(&QProcess::finished), this,
	                 &Editor::Compilation_Completed);
}

void Editor::Text_Changed() {
	this->text_changed = true;
}

void Editor::Compile_When_Needed(int tab_index) {
	if (tab_index != 1) {
		return;
	}
	if (!this->text_changed) {
		return;
	}
	this->text_changed = false;
	this->backend->Compile(ui->Backend_Code_Block->toPlainText());
}

void Editor::Compilation_Completed() {
	this->pdf_viewer->Refresh();
}

Editor::~Editor() {
	delete ui;
}
