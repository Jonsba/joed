#include "document_viewer.h"
#include "src/backend.h"

#include <QHBoxLayout>
#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfPageNavigation>
#include <QPdfView>
#include <QTreeView>

Document_Viewer::Document_Viewer(QWidget* parent, Backend* backend) : QWidget(parent) {
	this->backend = backend;

	this->bookmark_view = new QTreeView(this);
	this->pdf_document = new QPdfDocument(this);
	this->pdf_view = new QPdfView(this);
	this->pdf_view->setDocument(this->pdf_document);
	this->pdf_view->setPageMode(QPdfView::MultiPage);
	QPdfBookmarkModel* bookmark_model = new QPdfBookmarkModel(this);
	bookmark_model->setDocument(this->pdf_document);
	this->bookmark_view->setModel(bookmark_model);
	this->layout = new QHBoxLayout(this);
	this->layout->addWidget(this->bookmark_view);
	this->layout->addWidget(this->pdf_view);
	this->layout->setStretch(1, 7);
	this->setLayout(this->layout);
	parent->layout()->addWidget(this);

	QObject::connect(this->bookmark_view, &QTreeView::activated, this,
	                 &Document_Viewer::bookmark_selected);
}

void Document_Viewer::refresh() {
	this->pdf_document->load(this->backend->compiled_document_path());
}

void Document_Viewer::bookmark_selected(const QModelIndex& index) {
	const int page = index.data(QPdfBookmarkModel::PageNumberRole).toInt();
	this->pdf_view->pageNavigation()->setCurrentPage(page);
}
