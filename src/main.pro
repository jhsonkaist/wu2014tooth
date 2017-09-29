
DEPENDPATH += . ../include/vcg
INCLUDEPATH += . ../include/vcg
CONFIG += console c++11
TEMPLATE = app


TARGET = main
SOURCES += main.cpp ../include/vcg/wrap/ply/plylib.cpp