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
	src/abstract_loadable_tree.cpp \
	src/abstract_multi_block.cpp \
	src/abstract_non_layouted_block.cpp \
	src/backend.cpp \
	src/children_block.cpp \
	src/definitions_file.cpp \
	src/document.cpp \
	src/environment.cpp \
	src/escaper.cpp \
	src/frontend/abstract_document_viewer.cpp \
	src/frontend/children_widget_block.cpp \
	src/frontend/color_scheme.cpp \
	src/frontend/document_form.cpp \
	src/frontend/editor_form.cpp \
	src/frontend/html_viewer.cpp \
	src/frontend/multi_block_widget.cpp \
	src/frontend/pdf_viewer.cpp \
	src/frontend/text_block_widget.cpp \
	src/joed.cpp \
	src/joed_conf_file.cpp \
	src/layout_block.cpp \
	src/layout_entry.cpp \
	src/lua_client.cpp \
	src/lua_vm.cpp \
	src/main.cpp \
	src/raw_text_block.cpp \
	src/root_block.cpp \
	src/style.cpp \
	src/styles.cpp \
	src/text_block.cpp \
	src/writer.cpp

HEADERS += \
	src/abstract_block.h \
	src/abstract_loadable_file.h \
	src/abstract_loadable_object.h \
	src/abstract_loadable_tree.h \
	src/abstract_multi_block.h \
	src/abstract_non_layouted_block.h \
	src/backend.h \
	src/children_block.h \
	src/definitions_file.h \
	src/document.h \
	src/environment.h \
	src/escaper.h \
	src/field.h \
	src/frontend/abstract_document_viewer.h \
	src/frontend/children_widget_block.h \
	src/frontend/color_scheme.h \
	src/frontend/document_form.h \
	src/frontend/editor_form.h \
	src/frontend/html_viewer.h \
	src/frontend/multi_block_widget.h \
	src/frontend/pdf_viewer.h \
	src/frontend/text_block_widget.h \
	src/joed.h \
	src/joed_conf_file.h \
	src/layout_block.h \
	src/layout_entry.h \
	src/lua_client.h \
	src/lua_vm.h \
	src/raw_text_block.h \
	src/root_block.h \
	src/style.h \
	src/styles.h \
	src/text_block.h \
	src/writer.h

FORMS += \
	src/frontend/ui/document_form.ui \
	src/frontend/ui/editor_form.ui

INCLUDEPATH += \
	/usr/include/lua5.3
LIBS += \
	-llua5.3-c++

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	src/frontend/ui/icons.qrc
