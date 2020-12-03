#include "color_scheme.h"

Color_Scheme::Color_Scheme(int level) {
	this->hue = level * (360.0 / this->N_Color_Levels);
}

QPalette& Color_Scheme::palette(Widget_State state) {
	int lightness;
	int saturation = 200;
	switch (state) {
	case Widget_State::Active:
		lightness = 230;
		break;
	case Widget_State::Highlighted:
		lightness = 190;
		break;
	}
	QColor color;
	// hue: [0 - 359], saturation: [0 - 255], lightness: [0 - 255]
	color.setHsl(this->hue, saturation, lightness);
	this->the_palette.setColor(QPalette::Base, color);
	this->the_palette.setColor(QPalette::Background, color);
	return this->the_palette;
}
