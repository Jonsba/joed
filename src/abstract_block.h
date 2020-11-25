#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include <QString>

class Writer;
class Escaper;

enum class Block_Base_Type {
	Uninitialized_E,
	Layout_Block_E,
	Children_Block_E,
	Text_Block_E,
	Raw_Text_Block_E
};

enum class Block_Variant {
	Standard_E,
	// Text blocks only
	Title_E,
	Caption_E
	//
};

struct Block_Type {
	Block_Base_Type base;
	Block_Variant variant;
};

class Abstract_Block {
 public:
	Abstract_Block(QString identifier, Block_Type block_type);
	virtual ~Abstract_Block();
	QString identifier();
	Block_Type type();
	virtual QString translate(Escaper* escaper) = 0;
	virtual void save(Writer* writer, int level) = 0;
	//
	inline static const Block_Type Children_Block_Type = {Block_Base_Type::Children_Block_E,
	                                                      Block_Variant::Standard_E};
	inline static const Block_Type Raw_Text_Block_Type = {Block_Base_Type::Raw_Text_Block_E,
	                                                      Block_Variant::Standard_E};

 protected:
	void set_identifier(QString Identifier);

 private:
	const QString Identifier;
	const Block_Type Type;
};

#endif // ABSTRACT_BLOCK_H
