#ifndef ABSTRACT_LOADABLE_TREE_H
#define ABSTRACT_LOADABLE_TREE_H

#include "abstract_loadable_object.h"
#include <QString>

class Abstract_Loadable_Tree : public Abstract_Loadable_Object {
 public:
	// Although Definitions_Loader also indirectly derivates from Abstract_Loadable_Tree, the C++
	// standard doesn't allow it to access the protected methods of its internal
	// Abstract_Loadable_Tree objects, unless we define it as a friend class
	friend class Definitions_Loader;
	Abstract_Loadable_Tree();

 protected:
	virtual State process_key(QString key, int level) = 0;
};

#endif // ABSTRACT_LOADABLE_TREE_H
