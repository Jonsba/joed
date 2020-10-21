QT += core gui widgets pdfwidgets

CONFIG += c++17

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
    src/abstract_loadable_file.cpp \
    src/abstract_loadable_object.cpp \
    src/backend.cpp \
    src/children_blocks.cpp \
    src/definitions_file.cpp \
    src/frontend/document_controller.cpp \
    src/frontend/multi_block_widget.cpp \
    src/frontend/text_block_widget.cpp \
    src/joed.cpp \
    src/joed_conf_file.cpp \
    src/layout_entry.cpp \
    src/lua_vm.cpp \
    src/main.cpp \
    src/frontend/editor.cpp \
    src/multi_block.cpp \
    src/style.cpp \
    src/styles.cpp \
    src/text_block.cpp

HEADERS += \
	src/abstract_block.h \
	src/abstract_loadable_file.h \
	src/abstract_loadable_object.h \
	src/backend.h \
	src/children_blocks.h \
	src/definitions_file.h \
	src/frontend/document_controller.h \
    src/frontend/editor.h \ \
	src/frontend/multi_block_widget.h \
	src/frontend/text_block_widget.h \
	src/joed.h \
	src/joed_conf_file.h \
	src/layout_entry.h \
	src/lua_vm.h \
	src/multi_block.h \
	src/style.h \
	src/styles.h \
	src/text_block.h

FORMS += \
    src/frontend/ui/editor.ui

INCLUDEPATH += \
    /usr/include/lua5.3
LIBS += \
    -llua5.3-c++

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
