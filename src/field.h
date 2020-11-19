#ifndef FIELD_H
#define FIELD_H

#include <QStringList>

struct Field {
	struct Key {
		inline static const QString Backend = "backend";
		inline static const QString Blocks = "blocks";
		inline static const QString Child_Of = "child-of";
		inline static const QString Children = "children";
		inline static const QString Declare = "declare";
		inline static const QString Default_Child_Style = "default-child-style";
		inline static const QString Defaults = "defaults";
		inline static const QString Document = "document";
		inline static const QString Document_Class = "document-class";
		inline static const QString Doc_File_Ext = "doc-file-ext";
		inline static const QString Env_File_Ext = "env-file-ext";
		inline static const QString Environment = "environment";
		inline static const QString Escape_Table = "escape-table";
		inline static const QString Inherits = "inherits";
		inline static const QString Name = "name";
		inline static const QString Layout = "layout";
		inline static const QString Output = "output";
		inline static const QString Style = "style";
		inline static const QString Styles = "styles";
		inline static const QString Text = "text";
		inline static const QString Type = "type";
		inline static const QString Version = "format-version";
		inline static const QString Viewer = "viewer";
	};
	struct Value {
		inline static const QString Caption = "caption";
		inline static const QString HTML_Viewer = "html";
		inline static const QString Layout_Block = "layout_block";
		inline static const QString PDF_Viewer = "pdf";
		inline static const QString Text_Block = "text_block";
		inline static const QString Title = "title";
	};
	struct Id {
		inline static const QString Children_Block = "_children_";
		inline static const QString Compiled_Document = "_compiled_document_";
		inline static const QString Raw_Text_Block = "_raw_text_";
		inline static const QString Text_Content = "_text_content_";
		inline static const QString Translated_Document = "_translated_document_";
		inline static const QString Translated_Environment = "_translated_environment_";
	};
};

#endif // FIELD_H
