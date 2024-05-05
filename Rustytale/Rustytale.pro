QT += core gui
QT +=multimedia
QT +=core gui multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Soul.cpp \
    Sword.cpp \
    battleFrame.cpp \
    deerBlaster.cpp \
    gameButton.cpp \
    gameEngine.cpp \
    gunShoot.cpp \
    main.cpp \
    loadingInterface.cpp \
    myMenu.cpp \
    normalAttack.cpp \
    targetBar.cpp \
    textShower.cpp

HEADERS += \
    Soul.h \
    Sword.h \
    battleFrame.h \
    deerBlaster.h \
    gameButton.h \
    gameEngine.h \
    gunShoot.h \
    loadingInterface.h \
    myMenu.h \
    normalAttack.h \
    targetBar.h \
    textShower.h

FORMS += \
    loadingInterface.ui

TRANSLATIONS += \
    Rustytale_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
