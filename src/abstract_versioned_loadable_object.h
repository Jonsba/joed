#ifndef ABSTRACT_VERSIONED_LOADABLE_OBJECT_H
#define ABSTRACT_VERSIONED_LOADABLE_OBJECT_H

#include "abstract_loadable_object.h"
#include <QString>

struct File_Version {
	int Major;
	int Minor;
	int Revision;
};

class Abstract_Versioned_Loadable_Object : public Abstract_Loadable_Object {
 public:
	Abstract_Versioned_Loadable_Object(const File_Version Version);
	void check_version_validity(QString version_string);

	virtual State process_intermediate_key(QString key, int level) = 0;
	virtual void assign(QString end_key, QString value) = 0;

 private:
	File_Version Version;
};

#endif // ABSTRACT_VERSIONED_LOADABLE_OBJECT_H
