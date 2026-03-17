QT       += core gui opengl network sql openglwidgets core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Global.cpp \
    LoginWidget.cpp \
    OperaterWidget.cpp \
    QHCheckBox.cpp \
    TcpMgr.cpp \
    TipLabel.cpp \
    UserMgr.cpp \
    camwidget.cpp \
    clampwidget.cpp \
    customslider.cpp \
    downloadwidget.cpp \
    lockwidget.cpp \
    main.cpp \
    openwall_crypt/crypt_blowfish.c \
    openwall_crypt/crypt_gensalt.c \
    openwall_crypt/wrapper.c \
    qtbcrypt.cpp \
    zmqreceiverthread.cpp

HEADERS += \
    Global.h \
    LoginWidget.h \
    OperaterWidget.h \
    QHCheckBox.h \
    TcpMgr.h \
    TipLabel.h \
    UserMgr.h \
    camwidget.h \
    clampwidget.h \
    customslider.h \
    downloadwidget.h \
    lockwidget.h \
    openwall_crypt/crypt.h \
    openwall_crypt/crypt_blowfish.h \
    openwall_crypt/crypt_gensalt.h \
    openwall_crypt/ow-crypt.h \
    openwall_crypt/x86.S \
    qtbcrypt.h \
    singleton.h \
    zmqreceiverthread.h

FORMS += \
    LoginWidget.ui \
    OperaterWidget.ui \
    camwidget.ui \
    clampwidget.ui \
    downloadwidget.ui \
    lockwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cfg.qrc \
    img.qrc

DISTFILES += \
    build/Desktop_Qt_6_6_3_MSVC2019_64bit-Debug/debug/UserData.txt \
    build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/UserData \
    build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/debug/config.ini


# 包含路径
INCLUDEPATH += $$PWD/include
LIBS += $$PWD/lib/libzmq-mt-4_3_5.lib
