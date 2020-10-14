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
    src/abstract_block.cpp \
    src/backend.cpp \
    src/backend_translater.cpp \
    src/definitions_parser.cpp \
    src/document_root.cpp \
    src/frontend/multi_block_widget.cpp \
    src/frontend/text_block_widget.cpp \
    src/joed.cpp \
    src/layout_entry.cpp \
    src/main.cpp \
    src/frontend/editor.cpp \
    src/multi_block.cpp \
    src/style.cpp \
    src/styles.cpp \
    src/text_block.cpp

HEADERS += \
	src/abstract_block.h \
    src/backend.h \
	src/backend_translater.h \
	src/definitions_parser.h \
	src/document_root.h \
    src/frontend/editor.h \ \
	src/frontend/multi_block_widget.h \
	src/frontend/text_block_widget.h \
	src/joed.h \
	src/layout_entry.h \
	src/multi_block.h \
	src/style.h \
	src/styles.h \
	src/text_block.h

FORMS += \
    src/frontend/ui/editor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
