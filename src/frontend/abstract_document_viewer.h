#ifndef ABSTRACT_DOCUMENT_VIEWER_H
#define ABSTRACT_DOCUMENT_VIEWER_H

#include <QWidget>

class Backend;

class Abstract_Document_Viewer : public QWidget
{
public:
	explicit Abstract_Document_Viewer(QWidget* parent, Backend* backend);
	virtual void refresh() = 0;
protected:
	Backend* backend;

};

#endif // ABSTRACT_DOCUMENT_VIEWER_H
