#include "pdf_viewer.h"
#include "src/backend.h"

#include <QHBoxLayout>
#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfPageNavigation>
#include <QPdfView>
#include <QTreeView>

PDF_Viewer::PDF_Viewer(QWidget* parent, Backend* backend)
    : Abstract_Document_Viewer(parent, backend) {
	this->backend = backend;

	this->pdf_document = new QPdfDocument(this);
	QPdfBookmarkModel* bookmark_model = new QPdfBookmarkModel(this);
	bookmark_model->setDocument(this->pdf_document);
	this->bookmark_view = new QTreeView(this);
	this->bookmark_view->setModel(bookmark_model);
	this->bookmark_view->setHeaderHidden(true);
	this->pdf_view = new QPdfView(this);
	this->pdf_view->setDocument(this->pdf_document);
	this->pdf_view->setPageMode(QPdfView::MultiPage);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(this->bookmark_view);
	layout->addWidget(this->pdf_view);
	layout->setStretch(1, 7);
	this->setLayout(layout);
	parent->layout()->addWidget(this);

	QObject::connect(this->bookmark_view, &QTreeView::activated, this,
	                 &PDF_Viewer::bookmark_selected);
}

void PDF_Viewer::refresh() {
	this->pdf_document->load(this->backend->compiled_document()->path);
}

void PDF_Viewer::bookmark_selected(const QModelIndex& index) {
	const int page = index.data(QPdfBookmarkModel::PageNumberRole).toInt();
	this->pdf_view->pageNavigation()->setCurrentPage(page);
}
