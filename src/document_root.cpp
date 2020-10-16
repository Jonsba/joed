#include "document_root.h"
#include "compile_env.h"
#include "definitions_parser.h"
#include "frontend/multi_block_widget.h"
#include "joed.h"
#include "multi_block.h"
#include "styles.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QVBoxLayout>

Document_Root::Document_Root(QVBoxLayout* widget_container, QProcess* compile_process) {
	this->styles = new Styles();
	this->compile_env = new Compile_Env();
	Definitions_Parser(this->styles, this->compile_env);
	this->top_block = new Multi_Block(this->styles->find(Joed::Document_Key));
	this->top_widget_block = new Multi_Block_Widget(widget_container, this->top_block);
	this->compile_process = compile_process;
}

void Document_Root::compile_document() {

	QString code = this->top_block->compile();

	QFile file(TEX_DOCUMENT_PATH);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
	compile_process->setWorkingDirectory(TEX_WORKING_DIRECTORY);
	compile_process->start(this->compile_env->backend(), QStringList() << TEX_DOCUMENT);
}
