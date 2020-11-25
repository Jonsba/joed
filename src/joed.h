#ifndef JOED_H
#define JOED_H

#include <QDir>
#include <QHash>
#include <QStandardPaths>
#include <QString>

void error(QString text);
void echo(QString text);
void echo(int number);

class Joed {

 public:
	inline static const QString Sep = QDir::separator();
	inline static const QString Local_Data_Path =
		 QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0] + Sep + "joed" +
		 Sep;
	inline static const QString System_Data_Path =
		 QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[1] + Sep + "joed" +
		 Sep;
	inline static const QString Joed_Conf_File = System_Data_Path + "joed.conf";
	inline static const QString Generic_Classes_Path = System_Data_Path + "generic-classes" + Sep;
	inline static const QString Backend_Classes_Path = System_Data_Path + "backend-classes" + Sep;
	inline static const QString Default_Document_Path =
		 QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0] + Sep;
	inline static const QString New_Document_Name = "new-document.jod";
};

#endif // JOED_H
