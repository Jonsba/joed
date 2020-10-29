#ifndef DOCUMENT_VIEWER_H
#define DOCUMENT_VIEWER_H

#include <QWidget>

class QPdfDocument;
class QPdfView;
class QHBoxLayout;
class QTreeView;
class Backend;

class Document_Viewer : public QWidget {
 public:
	Document_Viewer(QWidget* parent, Backend* backend);
	void refresh();

 private:
	void bookmark_selected(const QModelIndex& index);
	Backend* backend;
	QHBoxLayout* layout;
	QPdfView* pdf_view;
	QPdfDocument* pdf_document;
	QTreeView* bookmark_view;
};

#endif // DOCUMENT_VIEWER_H
