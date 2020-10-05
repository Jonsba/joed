QT += core gui widgets pdfwidgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/backend.cpp \
    src/backend_translater.cpp \
    src/definitions_parser.cpp \
    src/document.cpp \
    src/joed.cpp \
    src/main.cpp \
    src/frontend/editor.cpp \
    src/style_list.cpp

HEADERS += \
    src/backend.h \
	src/backend_translater.h \
	src/definitions_parser.h \
	src/document.h \
    src/frontend/editor.h \ \
	src/joed.h \
	src/style_list.h

FORMS += \
    src/frontend/ui/editor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
