#ifndef STYLES_H
#define STYLES_H

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

class Raw_Styles {
 private:
	inline static Style CB_Style = {Field::Id::Children_Block, Style_Type::Children_E,
	                                Style_Variant::Standard_E, nullptr};
	inline static Style RTB_Style = {Field::Id::Raw_Text_Block, Style_Type::Raw_Text_E,
	                                 Style_Variant::Standard_E, nullptr};

 public:
	inline static Style* Children_Style = &CB_Style;
	inline static Style* Raw_Text_Style = &RTB_Style;
};

#endif // STYLES_H
