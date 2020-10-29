#include "html_viewer.h"
#include "src/backend.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextBrowser>

HTML_Viewer::HTML_Viewer(QWidget* parent, Backend* backend)
    : Abstract_Document_Viewer(parent, backend) {
	parent->layout()->addWidget(this);
	this->html_view = new QTextBrowser();
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(this->html_view);
	this->setLayout(layout);
}

void HTML_Viewer::refresh() {
	QFile html_file(this->backend->compiled_document_path());
	html_file.open(QIODevice::ReadOnly | QIODevice::Text);
	QString html_text = html_file.readAll();
	this->html_view->setHtml(html_text);
}
