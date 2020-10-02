#ifndef EDITOR_H
#define EDITOR_H

#include "src/backend.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {

 public:
	Editor(Backend *backend = nullptr, QWidget *parent = nullptr);
	~Editor();

 private:
	Ui::Editor *ui;
	Backend *backend;
	void Compile();
};

#endif // EDITOR_H
