#ifndef TRIANGLERENDERER_H
#define TRIANGLERENDERER_H

#include <QtQuick/QQuickItem>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QBasicTimer>

/*!
    \brief Class controls the process of rendering \ref RotatableTriangle.

    Class responsible for using raw OpenGL to draw an object.
    Two simple light sources is using for the color change purposes.
*/

class TriangleRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    TriangleRenderer();
    ~TriangleRenderer();

    void setAngleZ( qreal angle );
    qreal getAngleZ() const { return m_angle; }
    qreal getMaxAngleZ() const { return qreal(360.0); }

    void setWindow(QQuickWindow *window) { m_window = window; }
    void setViewportSize( const QSize &size );

public slots:
    /**
     * \brief Here all interesting things processes.
     */
    void paint();

private:
    void initShaders();

    qreal                   m_angle;        ///< Current angle.
    QSize                   m_viewPortSize; ///< Actual viewport.
    QOpenGLShaderProgram    *m_program;     ///< Shader programm.
    QQuickWindow            *m_window;      ///< QQuickWindow object.
};

#endif // TRIANGLERENDERER_H
