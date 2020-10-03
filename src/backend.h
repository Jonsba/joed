#ifndef BACKEND_H
#define BACKEND_H

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
