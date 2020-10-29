#include "editor_form.h"
#include "document_form.h"
#include "src/backend.h"
#include "src/document.h"
#include "ui_editor_form.h"

#include <QTextEdit>
#include <QVBoxLayout>

Editor_Form::Editor_Form(QString document_path, QWidget* parent) : QMainWindow(parent) {
	this->ui = new Ui::Editor_Form();
	ui->setupUi(this);
	// QHBoxLayout* top_container = new QHBoxLayout();
	// top_container->addWidget(this->ui->document_widget);
	//
	this->document_form = new Document_Form(this->ui->document_widget, document_path);
}
Editor_Form::~Editor_Form() {
	delete ui;
}
