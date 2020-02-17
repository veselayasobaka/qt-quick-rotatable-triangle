QT += qml quick

HEADERS += \
        h\rotatabletriangle.h \
        h\trianglerenderer.h

SOURCES += \
        main.cpp \
        src\rotatabletriangle.cpp \
        src\trianglerenderer.cpp

RESOURCES += qml.qrc \
        shaders.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


