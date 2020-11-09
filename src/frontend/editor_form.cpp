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
	this->document_form = new Document_Form(this->ui->document_widget, document_path);
	QObject::connect(this->ui->action_open, &QAction::triggered, this->document_form,
	                 &Document_Form::open);
	QObject::connect(this->ui->action_save, &QAction::triggered, this->document_form,
	                 &Document_Form::save);
	QObject::connect(this->ui->action_save_as, &QAction::triggered, this->document_form,
	                 &Document_Form::save_as);
}
Editor_Form::~Editor_Form() {
	delete ui;
}
