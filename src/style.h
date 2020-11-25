#ifndef STYLE_H
#define STYLE_H

#include "field.h"

enum class Style_Type { Undefined_E, Layouted_E, Children_E, Text_E, Raw_Text_E };

enum class Style_Variant {
	Standard_E,
	// Text styles only
	Title_E,
	Caption_E
	//
};

class Style_Properties;

struct Style {
	QString identifier;
	Style_Type type = Style_Type::Undefined_E;
	Style_Variant variant = Style_Variant::Standard_E;
	Style_Properties* properties = nullptr;
};

#endif // STYLE_H
