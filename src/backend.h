#ifndef BACKEND_H
#define BACKEND_H

#include <QProcess>
#include <QString>

class Backend {

 public:
	Backend(QProcess *process);
	void Compile(QString code);

 private:
	QProcess *process;
};

void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

#endif // BACKEND_H
