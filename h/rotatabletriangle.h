#ifndef ROTTRIANGLE_H
#define ROTTRIANGLE_H

#include <QtQuick/QQuickItem>
#include "trianglerenderer.h"

/*!
    \brief Plane triangle, rotating around z-axis.

    Item represents a rotating triangle for qml program.
    When the \ref rotate property changes, triangle changes rotation speed accordingly.
*/
class RotatableTriangle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY( qint32 rotate READ getSpeed WRITE changeSpeed )

public:
    RotatableTriangle();
    ~RotatableTriangle();

    qint32 getSpeed() const { return m_speed; }
    /**
     * \brief returns period in ms for timerEvent.
     */
    quint32 getFrameFreq() { return 12; }
    qint32 getMaxSpeed() { return 10; }
    void changeSpeed( qint32 rot );

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged( QQuickWindow *win );

private:
    void timerEvent(QTimerEvent *e) override;

    QBasicTimer         m_timer;        ///< Timer manages updating of Item.
    TriangleRenderer    *m_renderer;    ///< Reanderer object.
    qint32              m_speed;        ///< Current speed.

};

#endif // ROTTRIANGLE_H
