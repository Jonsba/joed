#ifndef COMPILER_H
#define COMPILER_H

#include <QString>

class Multi_Block;
class Abstract_Block;
class Compile_Env {
 public:
	Compile_Env();
	void Set_Backend(QString backend);
	QString Get_Backend();

 private:
	QString backend;
};

#endif // COMPILER_H
