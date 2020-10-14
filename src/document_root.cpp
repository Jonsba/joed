#include "document_root.h"
#include "backend_translater.h"
#include "definitions_parser.h"
#include "frontend/multi_block_widget.h"
#include "joed.h"
#include "multi_block.h"
#include "styles.h"

#include <QVBoxLayout>

Document_Root::Document_Root(QVBoxLayout* widget_container) {
	this->styles = new Styles();
	this->translater = new Backend_Translater();
	Definitions_Parser(this->styles, this->translater);
	this->top_block = new Multi_Block(this->styles->Find(Joed::Document_Key));
	this->top_widget_block = new Multi_Block_Widget(widget_container, this->top_block);
}
