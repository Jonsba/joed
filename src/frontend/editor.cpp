#include "editor.h"
#include "document_controller.h"
#include "src/backend.h"
#include "src/document.h"
#include "ui_editor.h"

#include <QLabel>
#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfPageNavigation>
#include <QProcess>
#include <QTabWidget>
#include <QTextEdit>
#include <qpdfview.h>

Editor::Editor(QString document_path, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Editor), pdf_document(new QPdfDocument(this)) {
	ui->setupUi(this);

	this->pdf_view = new QPdfView(ui->View_Mode_Tab);
	this->pdf_view->setDocument(this->pdf_document);
	this->pdf_view->setPageMode(QPdfView::MultiPage);
	ui->View_Mode_Layout->addWidget(this->pdf_view);

	QPdfBookmarkModel* bookmarkModel = new QPdfBookmarkModel(this);
	bookmarkModel->setDocument(this->pdf_document);
	ui->Bookmark_View->setModel(bookmarkModel);

	//	this->text_changed = true;
	this->document_controller = new Document_Controller(this->ui->Document_Area, document_path);
	this->compile_process = this->document_controller->compile_process();

	QObject::connect(ui->Mode_Tab, &QTabWidget::currentChanged, this, &Editor::Compile);
	QObject::connect(this->compile_process, qOverload<int>(&QProcess::finished), this,
	                 &Editor::Compilation_Completed);
	QObject::connect(ui->Bookmark_View, &QTreeView::activated, this, &Editor::Bookmark_Selected);
}

void Editor::Bookmark_Selected(const QModelIndex& index) {
	const int page = index.data(QPdfBookmarkModel::PageNumberRole).toInt();
	this->pdf_view->pageNavigation()->setCurrentPage(page);
}

void Editor::Compile(int tab_index) {
	if (tab_index != 1) {
		return;
	}
	this->document_controller->compile();
}

void Editor::Compilation_Completed() {
	this->pdf_document->load(
	    this->document_controller->document()->backend()->compiled_document_path());
}

Editor::~Editor() {
	delete ui;
}
