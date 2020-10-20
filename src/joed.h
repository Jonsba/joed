#ifndef JOED_H
#define JOED_H

#include <QStandardPaths>
#include <QString>

void error(QString text);
void print(QString text); // Debug
void print(int number);   // Debug

namespace Joed {

static const QString Local_Data_Path =
    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0] + "/joed/";
static const QString System_Data_Path =
    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[1] + "/joed/";
static const QString Base_Joed_Directory = "/home/jonas-travail/Documents/github/joed/install/";
static const QString Joed_Conf_File = Base_Joed_Directory + "joed.conf";
static const QString Base_Definitions_Directory = Base_Joed_Directory + "definitions/";
static const QString Definitions_File_Extension = ".def";

} // namespace Joed

#endif // JOED_H
