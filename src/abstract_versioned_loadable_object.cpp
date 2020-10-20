#include "abstract_versioned_loadable_object.h"
#include "joed.h"
#include <QStringList>

Abstract_Versioned_Loadable_Object::Abstract_Versioned_Loadable_Object(const File_Version Version) {
	this->Version = Version;
}

void Abstract_Versioned_Loadable_Object::check_version_validity(QString version_string) {
	QStringList version_list = version_string.split(".");
	int major_version = version_list.at(0).toInt();
	int minor_version = version_list.at(1).toInt();
	if (major_version != Version.Major || minor_version > Version.Minor) {
		print("Unsupporter version: " + version_string);
		error("Any version between " + QString::number(Version.Major) + ".0.0 and " +
		      QString::number(Version.Major) + "." + QString::number(Version.Minor) +
		      ".x are supported");
	}
}
