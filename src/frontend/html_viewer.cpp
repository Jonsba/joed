#include "html_viewer.h"
#include "src/backend.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextBrowser>

HTML_Viewer::HTML_Viewer(QWidget* parent, Backend* backend)
    : Abstract_Document_Viewer(parent, backend) {
	parent->layout()->addWidget(this);
	this->html_view = new QTextBrowser(parent);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(this->html_view);
	this->setLayout(layout);
}

void HTML_Viewer::refresh() {
	QFile html_file(this->backend->compiled_document()->path);
	html_file.open(QIODevice::ReadOnly | QIODevice::Text);
	QFile css_file(this->backend->translated_environment()->path);
	css_file.open(QIODevice::ReadOnly | QIODevice::Text);
	// QTextBrowser doesn't support external CSS files, so we will copy paste the CSS content
	// directly in the HTML content
	QString html_text =
	    html_file.readAll().replace("<head>", "<head><style>" + css_file.readAll() + "</style>");
	this->html_view->setHtml(html_text);
}
