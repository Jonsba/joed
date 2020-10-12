#include "editor.h"
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

Editor::Editor(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Editor), pdf_document(new QPdfDocument(this)) {
	ui->setupUi(this);
	ui->Backend_Code_Block->setFocus();

	this->pdf_view = new QPdfView(ui->View_Mode_Tab);
	this->pdf_view->setDocument(this->pdf_document);
	this->pdf_view->setPageMode(QPdfView::MultiPage);
	ui->View_Mode_Layout->addWidget(this->pdf_view);

	QPdfBookmarkModel* bookmarkModel = new QPdfBookmarkModel(this);
	bookmarkModel->setDocument(this->pdf_document);
	ui->Bookmark_View->setModel(bookmarkModel);

	this->text_changed = true;
	this->compilation_process = new QProcess();
	this->backend = new Backend(this->compilation_process);

	QObject::connect(ui->Backend_Code_Block, &QTextEdit::textChanged, this, &Editor::Text_Changed);
	QObject::connect(ui->Mode_Tab, &QTabWidget::currentChanged, this, &Editor::Compile_When_Needed);
	QObject::connect(this->compilation_process, qOverload<int>(&QProcess::finished), this,
	                 &Editor::Compilation_Completed);
	QObject::connect(ui->Bookmark_View, &QTreeView::activated, this, &Editor::Bookmark_Selected);

	this->document = new Document();
}

void Editor::Text_Changed() {
	this->text_changed = true;
	// Resize the block to fit its text
	QSize size = ui->Backend_Code_Block->document()->size().toSize();
	ui->Backend_Code_Block->setFixedHeight(size.height() + 3);
}

void Editor::Bookmark_Selected(const QModelIndex& index) {
	const int page = index.data(QPdfBookmarkModel::PageNumberRole).toInt();
	this->pdf_view->pageNavigation()->setCurrentPage(page);
}

void Editor::Compile_When_Needed(int tab_index) {
	if (tab_index != 1) {
		return;
	}
	if (! this->text_changed) {
		return;
	}
	this->text_changed = false;
	this->backend->Compile(ui->Backend_Code_Block->toPlainText());
}

void Editor::Compilation_Completed() {
	this->pdf_document->load(PDF_DOCUMENT_PATH);
}

Editor::~Editor() {
	delete ui;
}
