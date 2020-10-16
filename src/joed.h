#ifndef JOED_H
#define JOED_H

#include <QStandardPaths>
#include <QString>

void print(QString text); // Debug
void print(int number);   // Debug

typedef QVector<QString> QString_Vector;

namespace Joed {

static const QString Local_Data_Path =
    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0] + "/joed/";
static const QString System_Data_Path =
    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[1] + "/joed/";
static const QString Base_Definitions_File =
    "/home/jonas-travail/Documents/github/joed/install/backend/base.def";

} // namespace Joed

#endif // JOED_H
