#Common settings for Qmmp build

#Extra clean target

unix:QMAKE_DISTCLEAN += -r .build

#Some conf to redirect intermediate stuff in separate dirs

UI_DIR=./.build/ui/
MOC_DIR=./.build/moc/
OBJECTS_DIR=./.build/obj
RCC_DIR=./.build/rcc

#Defines

DEFINES += QT_NO_CAST_FROM_BYTEARRAY QT_STRICT_ITERATORS

equals(QT_MAJOR_VERSION, 5){
CONFIG -= depend_includepath
QT += widgets
unix:DEFINES += QMMP_WS_X11
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050400 QT_DEPRECATED_WARNINGS
}

#Configuration

CONFIG += hide_symbols
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -std=gnu11
DEFINES += QMMP_LIBRARY


#Version
TTK_VERSION = 4.1.2.0
QMMP_VERSION = 1.7.2
CONFIG += USE_STATIC_LIBRARY

#Comment/uncomment this if you want to change plugins list

CONFIG += BITCRUSHER_PLUGIN
CONFIG += BS2B_PLUGIN
CONFIG += CRYSTALIZER_PLUGIN
CONFIG += ECHO_PLUGIN
CONFIG += LADSPA_PLUGIN
CONFIG += MUFFLER_PLUGIN
CONFIG += SILENCE_PLUGIN
CONFIG += SONIC_PLUGIN
CONFIG += SOXR_PLUGIN
CONFIG += SRC_PLUGIN
CONFIG += SUBWOOFER_PLUGIN

CONFIG += AAC_PLUGIN
CONFIG += ADLMIDI_PLUGIN
CONFIG += CDAUDIO_PLUGIN
CONFIG += FFAP_PLUGIN
CONFIG += FFMPEG_PLUGIN
CONFIG += FLAC_PLUGIN
CONFIG += GME_PLUGIN
CONFIG += MUSEPACK_PLUGIN
CONFIG += WITH_MPG123
CONFIG += WITH_LIBCDDB
CONFIG += WITH_ENCA
CONFIG += OPUS_PLUGIN
CONFIG += SID_PLUGIN

#tracker features
CONFIG += TRACKER_PLUGIN

#zed features
CONFIG += ZED_PLUGIN

CONFIG -= $$DISABLED_PLUGINS

contains(CONFIG, USE_STATIC_LIBRARY){
    STATIC_LIBRARY_SUFFIX = _static
    DEFINES += TAGLIB_STATIC
}else{
    STATIC_LIBRARY_SUFFIX =
}
