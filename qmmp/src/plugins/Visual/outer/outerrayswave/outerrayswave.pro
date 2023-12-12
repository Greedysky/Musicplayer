include($$PWD/../../Visual.pri)

DESTDIR = $$PLUGINS_PREFIX/Visual

HEADERS += outerrayswave.h \
           visualouterrayswavefactory.h

SOURCES += outerrayswave.cpp \
           visualouterrayswavefactory.cpp

unix{
    QMAKE_CLEAN = $$DESTDIR/lib$${TARGET}.so
}
