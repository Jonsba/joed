#ifndef I_STYLED_BLOCK_H
#define I_STYLED_BLOCK_H

class Style;

class I_Styled_Block {
 public:
	I_Styled_Block(Style* the_style);
	Style* style();

 protected:
	Style* the_style;
};

#endif // I_STYLED_BLOCK_H
