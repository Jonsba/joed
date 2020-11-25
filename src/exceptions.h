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

namespace Exceptions {
   struct Not_Implemented : Exception {
		Not_Implemented() : Exception({Exception_Code::Other, "Not implemented!"}) {}
	};
	struct Invalid_Key : Exception {
		Invalid_Key() : Exception({Exception_Code::Invalid_Key, ""}) {}
	};
	struct Invalid_Value : Exception {
		Invalid_Value() : Exception({Exception_Code::Invalid_Value, ""}) {}
	};
	struct Invalid_Indent : Exception {
		Invalid_Indent() : Exception({Exception_Code::Invalid_Indent, ""}) {}
	};
	struct Cannot_Open : Exception {
		Cannot_Open(QString file_path)
		    : Exception({Exception_Code::Other, "Cannot open file '" + file_path + "'"}) {}
	};
}; // namespace Exceptions

#endif // EXCEPTIONS_H
