#ifndef EDITOR_H
#define EDITOR_H

#include "pdf_viewer.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {

 public:
	Editor(QWidget *parent = nullptr);
	~Editor();

 private:
	void Compile_When_Needed(int tab_index);
	void Compilation_Completed();
	void Text_Changed();

	Ui::Editor *ui;
	Backend *backend;
	QProcess *compilation_process;
	bool text_changed;
	PDF_Viewer *pdf_viewer;
};

#endif // EDITOR_H
