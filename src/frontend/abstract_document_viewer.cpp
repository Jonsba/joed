#include "abstract_document_viewer.h"
#include "src/backend.h"

Abstract_Document_Viewer::Abstract_Document_Viewer(QWidget* parent, Backend* backend)
    : QWidget(parent) {
	this->backend = backend;
}
