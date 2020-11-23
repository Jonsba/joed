#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>

enum class Exception_Code { Invalid_Key, Invalid_Value, Invalid_Indent, Other, Processed };

struct Exception {
	Exception(QString msg);
	Exception(Exception_Code code, QString msg);
	Exception_Code code = Exception_Code::Other;
	QString msg;
};

struct Invalid_Key_Exception : Exception {
	Invalid_Key_Exception() : Exception({Exception_Code::Invalid_Key, ""}) {}
};

struct Invalid_Value_Exception : Exception {
	Invalid_Value_Exception() : Exception({Exception_Code::Invalid_Value, ""}) {}
};

struct Invalid_Indent_Exception : Exception {
	Invalid_Indent_Exception() : Exception({Exception_Code::Invalid_Indent, ""}) {}
};

struct Cannot_Open_Exception : Exception {
	Cannot_Open_Exception(QString file_path)
	    : Exception({Exception_Code::Other, "Cannot open file '" + file_path + "'"}) {}
};

#endif // EXCEPTIONS_H
