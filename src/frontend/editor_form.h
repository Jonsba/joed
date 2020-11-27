#ifndef EDITOR_FORM_H
#define EDITOR_FORM_H

#include <QMainWindow>

class Document_Form;

QT_BEGIN_NAMESPACE
namespace Ui {
   class Editor_Form;
}
QT_END_NAMESPACE

class Editor_Form : public QMainWindow {

 public:
	Editor_Form(QString document_path, QWidget* parent = nullptr);
	~Editor_Form();

 public slots:
	void create();
	void open();
	void save();
	void save_as();

 private:
	Ui::Editor_Form* ui;
	Document_Form* document_form;
};

#endif // EDITOR_FORM_H
