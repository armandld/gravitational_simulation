TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++17 -g

SOURCES = \
    Astre.cc \
    Dessinable.cc \
    GenerateurAleatoire.cc \
    SupportADessin.cc \
    Systeme.cc \
    Vecteur3D.cc

HEADERS += \
    Astre.h \
    Dessinable.h \
    GenerateurAleatoire.h \
    SupportADessin.h \
    Systeme.h \
    Vecteur3D.h
