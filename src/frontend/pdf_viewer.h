#ifndef PDF_VIEWER_H
#define PDF_VIEWER_H

#include "src/backend.h"

#include <QLabel>
#include <poppler-qt5.h>

class PDF_Viewer : public QLabel {

 public:
	PDF_Viewer(QWidget *parent);
	void Refresh();

 private:
	Poppler::Document *pdf;
};

#endif // PDF_VIEWER_H
