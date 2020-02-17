#include "../h/trianglerenderer.h"

TriangleRenderer::TriangleRenderer()
{
    m_program = NULL;
    m_angle = 0;
    m_viewPortSize = QSize(0, 0);
}

TriangleRenderer::~TriangleRenderer()
{
    delete m_program;
}

void TriangleRenderer::setAngleZ(qreal angle)
{
    if ( m_angle >= getMaxAngleZ() )
    {
        m_angle = 0;
    }
    else
    {
        m_angle = angle;
    }
}

void TriangleRenderer::setViewportSize(const QSize &size)
{
    m_viewPortSize = size;
}

void TriangleRenderer::paint()
{
    if (!m_program)
    {
        initShaders();
    }

    if ( m_program )
    {
        m_program->bind();

        glViewport(0, 0, m_viewPortSize.width(), m_viewPortSize.height());
        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1);
        glClear( GL_COLOR_BUFFER_BIT );

        // definition of triangle geometry, color and light sources for the scene
        const GLfloat verticies[] =
        {
            0.0f, 0.8f,
            -0.6f, -0.6f,
            0.6f, -0.6f
        };
        // for this simple case we can simplify normal matrix definition
        const QVector3D normal =
        {
            0.0f, 0.0f, 1.0f
        };
        int vertsLoc = m_program->attributeLocation("VertexPosition");
        m_program->enableAttributeArray(vertsLoc);
        m_program->setAttributeArray(vertsLoc, GL_FLOAT, verticies, 2);

        //define MVP matrix
        int mMvpUniformLoc = m_program->uniformLocation("matrixMvp");
        int mModelUniformLoc = m_program->uniformLocation("matrixModel");
        int mViewUniformLoc = m_program->uniformLocation("matrixView");
        QMatrix4x4 matrixModel;
        matrixModel.rotate(m_angle, 0, 1.0f, 0);
        QMatrix4x4 matrixView;
        matrixView.translate(0, 0, -2.0f);
        QMatrix4x4 matProjection;
        matProjection.perspective(60.0f, 4.0f / 3.0f, 0.1f, 10.0f);
        QMatrix4x4 matrixMvp;
        matrixMvp = matProjection * matrixView * matrixModel;

        // setting up uniform values
        m_program->setUniformValue("normal", normal);
        m_program->setUniformValue(mMvpUniformLoc, matrixMvp);
        m_program->setUniformValue(mModelUniformLoc, matrixModel);
        m_program->setUniformValue(mViewUniformLoc, matrixView);

        // setting up light sources
        m_program->setUniformValue( "Light1Position", QVector3D(1.0, 0.0, 0.5) );
        m_program->setUniformValue( "Light1Intensity", QVector3D(1.0, 0.0, 0.0) );
        m_program->setUniformValue( "Light2Position", QVector3D(-0.7, 0.0, 1.0) );
        m_program->setUniformValue( "Light2Intensity", QVector3D(0.0, 0.0, 1.0) );
        m_program->setUniformValue( "MaterialReflection", QVector3D(0.4, 0.5, 0.2) );
        m_program->setUniformValue( "MirrorReflection", QVector3D(0.8, 0.8, 0.8) );
        m_program->setUniformValue( "Shininess", 70.5f );


        glDrawArrays( GL_TRIANGLES, 0, 3 );

        m_program->disableAttributeArray(vertsLoc);
        m_program->release();
    }

}

void TriangleRenderer::initShaders()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram;

    if ( m_program )
    {
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vert.glsl");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag.glsl");
        m_program->link();
    }
}
