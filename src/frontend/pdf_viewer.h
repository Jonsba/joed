#ifndef PDF_VIEWER_H
#define PDF_VIEWER_H

#include "abstract_document_viewer.h"
#include <QWidget>

class QPdfDocument;
class QPdfView;
class QHBoxLayout;
class QTreeView;
class Backend;

class PDF_Viewer : public Abstract_Document_Viewer {
 public:
	PDF_Viewer(QWidget* parent, Backend* backend);
	void refresh();

 private:
	void bookmark_selected(const QModelIndex& index);
	QPdfView* pdf_view;
	QPdfDocument* pdf_document;
	QTreeView* bookmark_view;
};

#endif // PDF_VIEWER_H
