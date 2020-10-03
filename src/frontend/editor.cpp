#include "editor.h"
#include "src/backend.h"
#include "ui_editor.h"

#include <QLabel>
#include <QPdfDocument>
#include <QPdfPageNavigation>
#include <QProcess>
#include <QTabWidget>
#include <QTextEdit>
#include <qpdfview.h>

Editor::Editor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Editor), pdf_document(new QPdfDocument(this)) {
	ui->setupUi(this);
	ui->Backend_Code_Block->setFocus();
	this->compilation_process = new QProcess();
	this->backend = new Backend(this->compilation_process);
	this->pdfView = new QPdfView(ui->View_Mode_Tab);
	this->pdfView->setDocument(this->pdf_document);
	this->pdfView->setPageMode(QPdfView::MultiPage);
	ui->View_Mode_Layout->addWidget(this->pdfView);

	QObject::connect(ui->Backend_Code_Block, &QTextEdit::textChanged, this, &Editor::Text_Changed);
	QObject::connect(ui->Mode_Tab, &QTabWidget::currentChanged, this, &Editor::Compile_When_Needed);
	QObject::connect(this->compilation_process, qOverload<int>(&QProcess::finished), this,
	                 &Editor::Compilation_Completed);

	this->text_changed = true;
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
	pdf_document->load("tex/document.pdf");
}

Editor::~Editor() {
	delete ui;
}
