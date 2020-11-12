#include "editor_form.h"
#include "document_form.h"
#include "src/backend.h"
#include "src/document.h"
#include "src/joed.h"
#include "ui_editor_form.h"

#include <QTextEdit>
#include <QVBoxLayout>

Editor_Form::Editor_Form(QString document_path, QWidget* parent) : QMainWindow(parent) {
	this->ui = new Ui::Editor_Form();
	ui->setupUi(this);
	this->document_form = new Document_Form(this->ui->document_widget);
	this->setWindowTitle(this->document_form->reset(document_path));
	QObject::connect(this->ui->action_new, &QAction::triggered, this, &Editor_Form::create);
	QObject::connect(this->ui->action_open, &QAction::triggered, this, &Editor_Form::open);
	QObject::connect(this->ui->action_save, &QAction::triggered, this, &Editor_Form::save);
	QObject::connect(this->ui->action_save_as, &QAction::triggered, this, &Editor_Form::save_as);
}

void Editor_Form::create() {
	this->setWindowTitle(this->document_form->reset());
}

void Editor_Form::open() {
	this->setWindowTitle(this->document_form->open());
}

void Editor_Form::save() {
	this->setWindowTitle(this->document_form->save());
}

void Editor_Form::save_as() {
	this->setWindowTitle(this->document_form->save_as());
}

Editor_Form::~Editor_Form() {
	delete ui;
}
