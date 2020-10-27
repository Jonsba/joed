#ifndef ABSTRACT_BLOCK_H
#define ABSTRACT_BLOCK_H

#include <QString>

enum class Block_Type {
	Uninitialized_E,
	Layout_Block_E,
	Children_Block_E,
	Text_Block_E,
	Raw_Text_Block_E
};

class Abstract_Block {
 public:
	Abstract_Block(QString Identifier, Block_Type Block_Type);
	QString identifier();
	Block_Type type();
	virtual QString translate() = 0;
	//
	inline static const QString Layout_Block_Value = "layout_block";
	inline static const QString Text_Block_Value = "text_block";
	inline static const QString Children_Block_Id = "_children_";
	inline static const QString Raw_Text_Block_Id = "_raw_text_";
	inline static const QString Text_Content_Id = "_text_content_";

 protected:
	void set_identifier(QString Identifier);

 private:
	const QString Identifier;
	const Block_Type Type;
};

#endif // ABSTRACT_BLOCK_H
