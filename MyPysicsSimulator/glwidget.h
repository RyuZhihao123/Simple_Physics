#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include "terraincollider.h"
#include "collider.h"
#define PI 3.1415926

class GLWidget  : public QOpenGLWidget , public QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QTimer m_timer;

    bool m_polygonMode;

protected:
    void initializeGL();
    void resizeGL(int w, int h);

    void paintGL();

    // shader programs
    QOpenGLShaderProgram* m_pointProgram;
    QOpenGLShaderProgram* m_skeletonProgram;
    QOpenGLShaderProgram* m_meshProgram;

    // Textures
    QOpenGLTexture* m_barkTexture;
    QOpenGLTexture* m_leafTexture;

    void initShaders(QOpenGLShaderProgram *&m_program, const QString &shaderName, bool v, bool c, bool n, bool t);
    void setupShaders(QOpenGLShaderProgram*& m_program);
    void setupTexture(QOpenGLTexture*& texture,const QString& filename);

    // rendering related
    QMatrix4x4 m_projectMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_modelMat;
    QVector3D m_eyePos,m_eyeDist;

    QPoint m_clickpos;
    double m_horAngle,m_verAngle;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    double distance;
    double scale;
    void wheelEvent(QWheelEvent* event);

    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_gameCycle();
};

#endif // GLWIDGET_H
