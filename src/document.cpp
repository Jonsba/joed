#include "document.h"
#include "backend_translater.h"
#include "definitions_parser.h"
#include "joed.h"
#include "style_list.h"

Document::Document() {
	this->styles = new Style_List();
	this->translater = new Backend_Translater();
	this->definitions_parser = new Definitions_Parser(this->styles, this->translater);
	print("Done");
}
