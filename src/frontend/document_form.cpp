#include "document_form.h"
#include "block_widget.h"
#include "focus_manager.h"
#include "html_viewer.h"
#include "pdf_viewer.h"
#include "ui_document_form.h"

#include "src/abstract_multi_block.h"
#include "src/backend.h"
#include "src/document.h"

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
	} catch (Exception& exception) {
		if (document_path == "") {
			this->error_box("Fatal error while creating a new document", exception.msg);
			abort();
		} else {
			this->error_box("Cannot open the document", exception.msg);
		}
	}
	if (this->document->backend()->compiled_document()->type == Field::Value::PDF_Viewer) {
		this->document_viewer.reset(
		    new PDF_Viewer(this->ui->view_mode_tab, this->document->backend()));
	} else {
		this->document_viewer.reset(
		    new HTML_Viewer(this->ui->view_mode_tab, this->document->backend()));
	}
	this->focus_manager.reset(new Focus_Manager());
	this->top_block_widget.reset(
	    new Block_Widget({this->ui->document_area, this->ui->scroll_area, this->focus_manager.get()},
	                     (Abstract_Multi_Block*)this->document->root_block(), 0, false));
	this->ui->document_area->layout()->addWidget(this->top_block_widget.get());
	this->focus_manager->focus_neighboor(this->top_block_widget.get());

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
	try {
		this->document->compile();
	} catch (Exception& exception) {
		this->error_box("Cannot compile the document because of an issue with class files",
		                exception.msg);
		this->ui->mode_tab->setCurrentIndex(0);
	}
}

void Document_Form::compilation_completed() {
	this->document_viewer->refresh();
}

void Document_Form::error_box(QString title, QString msg) {
	QMessageBox msg_box;
	msg_box.setStyleSheet("QLabel{min-width: 500px;}");
	msg_box.setText("<b>" + title + "</b>");
	msg_box.setInformativeText(msg);
	msg_box.exec();
}

Document_Form::~Document_Form() {
	delete this->ui;
}
