#ifndef DOCUMENT_FORM_H
#define DOCUMENT_FORM_H

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

 private:
	void create_ui(QWidget* parent);
	void compile(int tab_index);
	void compilation_completed();

	Ui::Document_Form* ui;
	Abstract_Document_Viewer* document_viewer;
	Multi_Block_Widget* top_widget_block;
	Document* document;
};

#endif // DOCUMENT_FORM_H
