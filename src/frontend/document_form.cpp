#include "document_form.h"
#include "abstract_document_viewer.h"
#include "html_viewer.h"
#include "multi_block_widget.h"
#include "pdf_viewer.h"
#include "src/abstract_multi_block.h"
#include "src/backend.h"
#include "src/document.h"
#include "ui_document_form.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

Document_Form::Document_Form(QWidget* parent) : QWidget(parent) {
	this->ui = new Ui::Document_Form();
	this->ui->setupUi(this);
	parent->layout()->addWidget(this);
	QObject::connect(ui->mode_tab, &QTabWidget::currentChanged, this, &Document_Form::compile);
}

void Document_Form::reset_ui(QString document_path) {
	try {
		this->document.reset(new Document(document_path));
	} catch (Parse_Exception& exception) {
		QMessageBox msgBox;
		if (document_path == "") {
			msgBox.setText("Error while creating new document:");
		} else {
			msgBox.setText("Error while opening document:");
		}
		msgBox.setInformativeText(exception.msg);
		msgBox.exec();
	}

	if (this->document->backend()->compiled_document()->type == Field::Value::PDF_Viewer) {
		this->document_viewer.reset(
		    new PDF_Viewer(this->ui->view_mode_tab, this->document->backend()));
	} else {
		this->document_viewer.reset(
		    new HTML_Viewer(this->ui->view_mode_tab, this->document->backend()));
	}

	this->top_widget_block.reset(new Multi_Block_Widget(
	    this->ui->document_area, (Abstract_Multi_Block*)this->document->root_block(), 0));
	this->ui->document_area->layout()->addWidget(this->top_widget_block.get());

	QObject::connect(this->document->compile_process(), qOverload<int>(&QProcess::finished), this,
	                 &Document_Form::compilation_completed);
}

QString Document_Form::reset(QString document_path) {
	this->reset_ui(document_path);
	this->ui->mode_tab->setCurrentIndex(0);
	if (document_path == "") {
		return "<New Document>";
	}
	return document_path;
}

QString Document_Form::open() {
	QString document_path = this->launch_dialog("Open Document", QFileDialog::AcceptOpen);
	if (document_path == "") {
		return this->document->path();
	}
	this->reset_ui(document_path);
	this->ui->mode_tab->setCurrentIndex(0);
	return document_path;
}

QString Document_Form::save() {
	if (this->document->path() == "") {
		return this->save_as();
	} else {
		this->document->save();
	}
	return this->document->path();
}

QString Document_Form::save_as() {
	QString document_path = this->launch_dialog("Save Document As", QFileDialog::AcceptSave);
	if (document_path == "") {
		return this->document->path();
	}
	this->document->save_as(document_path);
	return document_path;
}

QString Document_Form::launch_dialog(QString title, QFileDialog::AcceptMode mode) {
	QFileDialog dialog(this, title);
	dialog.setDirectory(Joed::Default_Document_Path);
	if (this->document->path() != "") {
		dialog.setDirectory(QFileInfo(this->document->path()).dir().path());
	}
	dialog.setAcceptMode(mode);
	dialog.setNameFilter("Document Files (*.jod)");
	dialog.setDefaultSuffix("jod");
	if (dialog.exec() != QDialog::Accepted) {
		return "";
	}
	return dialog.selectedFiles().first();
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

Document_Form::~Document_Form() {
	delete this->ui;
}
