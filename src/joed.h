#ifndef JOED_H
#define JOED_H

#include <QStandardPaths>
#include <QString>

void print(QString text);

namespace Joed {

static const QString Local_Data_Path =
    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0] + "/joed/";
static const QString System_Data_Path =
    QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[1] + "/joed/";
static const QString Base_Definitions_File =
    "/home/jonas-travail/Documents/github/joed/install/backend/base.def";

static const QString Version_Key = "version";
static const QString Backend_Key = "backend";
static const QString Styles_Key = "styles";
static const QString Document_Key = "document";
static const QString New_Style_Key = "new-style";
static const QString Name_Key = "name";
static const QString Child_Of_Key = "child-of";
static const QString Type_Key = "type";
static const QString Layout_Key = "layout";
static const QString Declare_Key = "declare";
static const QString Output_Key = "output";
static const QString Inherits_Key = "inherits";
static const QString Default_Child_Style_Key = "default-child-style";
static const QString Keys[] = {Version_Key,
                               Backend_Key,
                               Styles_Key,
                               Document_Key,
                               New_Style_Key,
                               Name_Key,
                               Child_Of_Key,
                               Type_Key,
                               Layout_Key,
                               Declare_Key,
                               Output_Key,
                               Inherits_Key,
                               Default_Child_Style_Key};

} // namespace Joed

#endif // JOED_H
