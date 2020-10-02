#include "pdf_viewer.h"
#include "src/backend.h"

PDF_Viewer::PDF_Viewer(QWidget *parent) : QLabel(parent) {}

void PDF_Viewer::Refresh() {
	this->pdf = Poppler::Document::load("tex/document.pdf");
	pdf->setRenderHint(Poppler::Document::TextAntialiasing);

	// Access page of the PDF file
	Poppler::Page *pdf_page = pdf->page(0); // Document starts at page 0

	// Generate a QImage of the rendered page
	QImage image = pdf_page->renderToImage();

	// ... use image ...
	// this is how usually we do it with Qt
	this->setPixmap(QPixmap::fromImage(image));

	// after the usage, the page must be deleted
	delete pdf_page;
	delete this->pdf;
}
