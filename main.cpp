#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "h/rotatabletriangle.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<RotatableTriangle>("RotTriangle", 1, 0, "RotatableTriangle");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
