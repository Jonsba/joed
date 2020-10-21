#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class Backend;
class Document_Controller;

class QProcess;
class QPdfDocument;
class QPdfView;

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {

 public:
	Editor(QString document_path, QWidget* parent = nullptr);
	~Editor();

 private:
	void Bookmark_Selected(const QModelIndex& index);
	void Compile(int tab_index);
	void Compilation_Completed();

	Ui::Editor* ui;
	QProcess* compile_process;
	//	bool text_changed;
	QPdfView* pdf_view;
	QPdfDocument* pdf_document;
	Document_Controller* document_controller;
};

#endif // EDITOR_H
