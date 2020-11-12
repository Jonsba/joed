#ifndef DOCUMENT_FORM_H
#define DOCUMENT_FORM_H

#include "src/joed.h"
#include <QScopedPointer>
#include <QWidget>

class Backend;
class Document;
class Multi_Block_Widget;
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
	Document_Form(QWidget* parent, QString document_path);
	~Document_Form();

 public slots:
	void open();
	void save();
	void save_as();

 private:
	void create_ui(QString document_path);
	void compile(int tab_index);
	void compilation_completed();

	Ui::Document_Form* ui;
	QScopedPointer<Abstract_Document_Viewer> document_viewer;
	QScopedPointer<Multi_Block_Widget> top_widget_block;
	QScopedPointer<Document> document;
};

#endif // DOCUMENT_FORM_H
