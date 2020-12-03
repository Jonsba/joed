#ifndef STYLE_H
#define STYLE_H

#include "field.h"

enum class Style_Type { Undefined, Layouted, Children, Text, Raw_Text };

enum class Style_Variant {
	Standard,
	// Text styles only
	Title,
	Caption
	//
};

class Style_Properties;

struct Style {
	QString identifier;
	Style_Type type = Style_Type::Undefined;
	Style_Variant variant = Style_Variant::Standard;
	Style_Properties* properties = nullptr;
};

#endif // STYLE_H
