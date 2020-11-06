#include "document_form.h"
#include "abstract_document_viewer.h"
#include "html_viewer.h"
#include "multi_block_widget.h"
#include "pdf_viewer.h"
#include "src/abstract_multi_block.h"
#include "src/backend.h"
#include "src/document.h"
#include "ui_document_form.h"

#include <QProcess>

Document_Form::Document_Form(QWidget* parent, QString document_path) : QWidget(parent) {
	this->document = new Document(document_path);
	this->create_ui(parent);
}

void Document_Form::create_ui(QWidget* parent) {
	this->ui = new Ui::Document_Form();
	this->ui->setupUi(this);
	parent->layout()->addWidget(this);
	if (this->document->backend()->viewer_type() == Backend::PDF_Viewer_Id) {
		this->document_viewer = new PDF_Viewer(this->ui->View_Mode_Tab, this->document->backend());
	} else {
		this->document_viewer = new HTML_Viewer(this->ui->View_Mode_Tab, this->document->backend());
	}

	QObject::connect(ui->Mode_Tab, &QTabWidget::currentChanged, this, &Document_Form::compile);
	QObject::connect(this->document->compile_process(), qOverload<int>(&QProcess::finished), this,
	                 &Document_Form::compilation_completed);

	this->top_widget_block = new Multi_Block_Widget(
	    this->ui->Document_Area, (Abstract_Multi_Block*)this->document->root_block());
	this->ui->Document_Area->layout()->addWidget(this->top_widget_block);
}

void Document_Form::compile(int tab_index) {
	if (tab_index != 1) {
		return;
	}
	this->document->compile();
}

void Document_Form::compilation_completed() {
	this->document_viewer->refresh();
}
