QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -fconcepts-diagnostics-depth=200

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/block.cpp \
    model/entity/enemyentity.cpp \
    model/entity/energypackentity.cpp \
    model/entity/entity.cpp \
    model/entity/healthpackentity.cpp \
    model/entity/penemyentity.cpp \
    model/entity/poisonedterrainentity.cpp \
    model/entity/portalentity.cpp \
    model/entity/xenemyentity.cpp \
    view/renderer/colorrenderer.cpp \
    view/graphicsItem/damagegraphicsitem.cpp \
    view/graphicsItem/enemygraphicsitem.cpp \
    view/graphicsItem/energypackgraphicsitem.cpp \
    view/gamescene.cpp \
    main.cpp \
    view/graphicsItem/healthpackgraphicsitem.cpp \
    view/mainwindow.cpp \
    model/gameworld.cpp \
    model/player.cpp \
    controller/Controller.cpp \
    controller/GUIController.cpp \
    controller/TextController.cpp \
    view/renderer/overlayrenderer.cpp \
    view/graphicsItem/penemygraphicsitem.cpp \
    view/graphicsItem/playergraphicsitem.cpp \
    view/graphicsItem/portalgraphicsitem.cpp \
    view/graphicsItem/pterraingraphicsitem.cpp \
    view/spritesheetmanager.cpp \
    view/renderer/textrenderer.cpp \
    view/graphicsItem/tilegraphicsitem.cpp \
    view/graphicsItem/tilegraphicspixmapitem.cpp \
    view/graphicsItem/xenemygraphicsitem.cpp \
    model/pathfinderadapter.cpp \
    model/pathnode.cpp

HEADERS += \
    model/entity/energypackentity.h \
    model/level.h \
    model/behaviour.h \
    model/BlockType.h \
    model/block.h \
    model/entity/enemyentity.h \
    model/entity/entity.h \
    model/entity/healthpackentity.h \
    model/entity/penemyentity.h \
    model/entity/poisonedterrainentity.h \
    model/entity/portalentity.h \
    model/entity/xenemyentity.h \
    view/renderer/colorrenderer.h \
    view/graphicsItem/damagegraphicsitem.h \
    view/graphicsItem/enemygraphicsitem.h \
    view/graphicsItem/energypackgraphicsitem.h \
    view/gamescene.h \
    view/graphicsItem/healthpackgraphicsitem.h \
    view/mainwindow.h \
    model/direction.h \
    model/gameworld.h \
    model/player.h \
    controller/Controller.h \
    controller/GUIController.h \
    controller/TextController.h \
    view/renderer/overlayrenderer.h \
    view/graphicsItem/penemygraphicsitem.h \
    view/graphicsItem/playergraphicsitem.h \
    view/graphicsItem/portalgraphicsitem.h \
    view/graphicsItem/pterraingraphicsitem.h \
    view/spritesheetmanager.h \
    view/renderer/textrenderer.h \
    view/graphicsItem/tilegraphicsitem.h \
    view/graphicsItem/tilegraphicspixmapitem.h \
    view/graphicsItem/xenemygraphicsitem.h \
    model/pathfinderadapter.h \
    model/pathnode.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/ -lworld

INCLUDEPATH += $$PWD/worldsource
DEPENDPATH += $$PWD/worldsource
INCLUDEPATH += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/release
DEPENDPATH += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/ -lworld
else:unix: LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3-Debug/ -lworld
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/ -lworld

else:win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/libworld.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/libworld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/world.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/world.lib
else:win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/libworld.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/libworld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/release/world.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/debug/world.lib

else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/debug/ -lworld

else:win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/release/libworld.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/debug/libworld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/release/world.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/worldsource/build/Desktop_Qt_6_7_3_MinGW_64_bit-Release/debug/world.lib
