#ifndef ABSTRACT_LOADABLE_TREE_H
#define ABSTRACT_LOADABLE_TREE_H

#include "abstract_loadable_object.h"
#include <QString>

class Abstract_Loadable_Tree : public Abstract_Loadable_Object {
 public:
	Abstract_Loadable_Tree();

	virtual State process_key(QString key, int level) = 0;
};

#endif // ABSTRACT_LOADABLE_TREE_H
