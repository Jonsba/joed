#ifndef BACKEND_H
#define BACKEND_H

#define DOCUMENT_NAME "document"
#define TEX_DOCUMENT DOCUMENT_NAME ".tex"
#define TEX_WORKING_DIRECTORY "/home/jonas-travail/Documents/github/joed/build/tex/"
#define TEX_DOCUMENT_PATH TEX_WORKING_DIRECTORY TEX_DOCUMENT
#define PDF_DOCUMENT_PATH TEX_WORKING_DIRECTORY DOCUMENT_NAME ".pdf"

class QProcess;
class QString;

class Backend {

 public:
	Backend(QProcess *process);
	void Compile(QString code);

 private:
	QProcess *process;
};

#endif // BACKEND_H
