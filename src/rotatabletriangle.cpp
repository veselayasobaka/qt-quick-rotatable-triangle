#include "../h/rotatabletriangle.h"

#include <QtQuick/QQuickWindow>

RotatableTriangle::RotatableTriangle()
{
    m_renderer = NULL;
    m_timer.start(getFrameFreq(), this);
    m_speed = 0;

    connect( this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

RotatableTriangle::~RotatableTriangle()
{
    delete m_renderer;
}

void RotatableTriangle::changeSpeed(qint32 rot)
{
    // getMaxSpeed() defines maximum of velocity
    if ( 1 == rot && m_speed < getMaxSpeed() )
    {
        ++m_speed;
    }
    else if ( -1 == rot && m_speed > -getMaxSpeed() )
    {
        --m_speed;
    }
    else
    {
        // do nothing
    }
    qDebug() << "Current speed: " << getSpeed() << endl;
}

void RotatableTriangle::sync()
{
    // at first call create renderer object
    if (!m_renderer)
    {
        m_renderer = new TriangleRenderer;
        connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()), Qt::DirectConnection);
    }

    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
}

void RotatableTriangle::cleanup()
{
    if (!m_renderer)
    {
        delete m_renderer;
        m_renderer = NULL;
    }
}

void RotatableTriangle::handleWindowChanged(QQuickWindow *win)
{
    if (win)
    {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void RotatableTriangle::timerEvent(QTimerEvent *e)
{
    if ( m_renderer )
    {
        m_renderer->setAngleZ( m_renderer->getAngleZ() + 0.1 * m_speed );
        window()->update();
    }
}
