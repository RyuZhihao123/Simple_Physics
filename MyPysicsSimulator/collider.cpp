#include "collider.h"

QVector<Collider> m_balls;

Collider::Collider()
{
    color = QVector3D(qrand()/(float)RAND_MAX,
                      qrand()/(float)RAND_MAX,
                      qrand()/(float)RAND_MAX);
}

void Collider::RenderCollider(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat)

{
    QMatrix4x4 mat = modelMat;

    mat.translate(pos);

    this->RenderMesh(program, mat);
}

void Collider::Move()
{
    QVector3D N;  // 表面法向量
    bool collied = m_terrain.Collide(this->pos, this->dir.normalized(),this->bsphere.r,N);

    if(collied)
    {
        this->dir = dir - 2*(QVector3D::dotProduct(dir,N))*N;
    }

    pos += dir*bsphere.r*0.3f;
}
