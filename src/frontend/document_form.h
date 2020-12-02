#ifndef DOCUMENT_FORM_H
#define DOCUMENT_FORM_H

#include "src/joed.h"
#include <QFileDialog>
#include <QScopedPointer>
#include <QWidget>

class Backend;
class Document;
class Block_Widget;
class QWidget;
class QProcess;
class Abstract_Document_Viewer;

QT_BEGIN_NAMESPACE
namespace Ui {
   class Document_Form;
}
QT_END_NAMESPACE

class Document_Form : public QWidget {
 public:
	Document_Form(QWidget* parent);
	~Document_Form();
	QString reset(QString document_path = "");
	QString open();
	QString save();
	QString save_as();

 private:
	void reset_ui(QString document_path);
	QString launch_dialog(QString title, QFileDialog::AcceptMode mode);
	void compile(int tab_index);
	void compilation_completed();
	void error_box(QString title, QString msg);

	Ui::Document_Form* ui;
	QScopedPointer<Abstract_Document_Viewer> document_viewer;
	QScopedPointer<Block_Widget> top_widget_block;
	QScopedPointer<Document> document;
};

#endif // DOCUMENT_FORM_H
