#ifndef DOCUMENT_H
#define DOCUMENT_H

class Definitions_Parser;
class Styles;
class Multi_Block;
class Multi_Block_Widget;
class Backend_Translater;
class QVBoxLayout;

class Document_Root {
 public:
	Document_Root(QVBoxLayout* container_widget);

 private:
	Styles* styles;
	Multi_Block* top_block;
	Multi_Block_Widget* top_widget_block;
	Backend_Translater* translater;
};

#endif // DOCUMENT_H
