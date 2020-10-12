#ifndef DOCUMENT_H
#define DOCUMENT_H

class Definitions_Parser;
class Backend_Translater;
class Style_List;

class Document {
 public:
	Document();

 private:
	Definitions_Parser* definitions_parser;
	Style_List* styles;
	Backend_Translater* translater;
};

#endif // DOCUMENT_H
