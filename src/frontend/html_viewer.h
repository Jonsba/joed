#ifndef HTML_VIEWER_H
#define HTML_VIEWER_H

#include "abstract_document_viewer.h"
#include <QWidget>

class Backend;
class QTextBrowser;

class HTML_Viewer : public Abstract_Document_Viewer {
 public:
	HTML_Viewer(QWidget* parent, Backend* backend);
	void refresh();

 private:
	QTextBrowser* html_view;
};

#endif // HTML_VIEWER_H
