
#Vectorlist Math Libraries

TARGET += vmld

CONFIG += c++11 staticlib warn_off
TEMPLATE = lib
QT += gui

INCLUDEPATH += src/

HEADERS += src/color.h \
    src/image.h \
    src/performance.h \
    src/Random.h \
    src/rtmath.h \
    src/vec3f.h \

SOURCES += src/color.cpp \
    src/image.cpp \
    src/performance.cpp \
    src/Random.cpp \
    src/rtmath.cpp \
    src/vec3f.cpp \

CONFIG(debug, debug|release){
    DESTDIR = debug
}else{
    DESTDIR = release
}
