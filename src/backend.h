#ifndef BACKEND_H
#define BACKEND_H

#include <QString>

class Backend {

 public:
	Backend();
	void Compile(QString code);
};

#endif // BACKEND_H
