#ifndef COMPILER_H
#define COMPILER_H

#include <QString>

class Multi_Block;
class Abstract_Block;
class Compile_Env {
 public:
	Compile_Env();
	void set_backend(QString backend);
	QString backend();

 private:
	QString the_backend;
};

#endif // COMPILER_H
