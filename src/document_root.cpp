#include "document_root.h"
#include "compile_env.h"
#include "definitions_parser.h"
#include "frontend/multi_block_widget.h"
#include "initializer.h"
#include "joed.h"
#include "multi_block.h"
#include "style.h"
#include "styles.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>

Document_Root::Document_Root(QVBoxLayout* widget_container, QProcess* compile_process) {
	this->styles_initializer = new Initializer<Styles>(Style::Intermediate_Keys, Style::End_Keys);
	this->compile_env_initializer = new Initializer<Compile_Env>({}, Compile_Env::Backend_Keys);
	Definitions_Parser(this->styles_initializer, this->compile_env_initializer);
	this->styles = this->styles_initializer->built_object();
	this->top_block = new Multi_Block(this->styles->find(Style::Document_Key));
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
	QString backend_exec = this->compile_env_initializer->built_object()->backend_exec();
	compile_process->start(backend_exec, QStringList() << TEX_DOCUMENT);
}
