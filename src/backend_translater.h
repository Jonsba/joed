#ifndef BACKEND_TRANSLATER_H
#define BACKEND_TRANSLATER_H

#include <QString>

class Backend_Translater {
 public:
	Backend_Translater();
	void Set_Backend(QString backend);

 private:
	QString backend;
};

#endif // BACKEND_TRANSLATER_H
