#ifndef COLLIDER_H
#define COLLIDER_H
#include "meshloader.h"
#include "terraincollider.h"

class Collider: public MeshLoader
{
public:
    Collider();

    QVector3D pos;
    QVector3D dir = QVector3D(0,1.0,0);

    QVector3D color;

    void RenderCollider(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat);
    void Move();

};

extern QVector<Collider> m_balls;

#endif // COLLIDER_H
