QT += core gui opengl widgets
contains(QT_VERSION, ^6\\..*) {
    QT += openglwidgets
}
QMAKE_CXXFLAGS += -std=c++17

win32:LIBS += -lopengl32


TARGET = version_finale_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glsphere.cc \
    glwidget.cc \
    vue_opengl.cc

HEADERS += \
    glsphere.h \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
    ../general/Systeme.h

RESOURCES += \
    resource.qrc
