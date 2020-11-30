#ifndef COLOR_SCHEME_H
#define COLOR_SCHEME_H

#include <QPalette>

enum class Widget_State { Active_E, Highlighted_E };

class Color_Scheme {
 public:
	Color_Scheme(int level);
	QPalette& palette(Widget_State state = Widget_State::Active_E);

 private:
	const int N_Color_Levels = 7;
	int hue;
	QPalette the_palette;
};

#endif // COLOR_SCHEME_H
