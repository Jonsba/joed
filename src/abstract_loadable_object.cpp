#include "abstract_loadable_object.h"

Abstract_Loadable_Object::Abstract_Loadable_Object(QStringList keys_style_values) {
	this->keys_style_values = keys_style_values;
}

bool Abstract_Loadable_Object::is_key_object(QString end_key) {
	if (this->keys_style_values.indexOf(end_key) >= 0) {
		return true;
	}
	return false;
}
