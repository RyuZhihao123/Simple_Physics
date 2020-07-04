#include "utils.h"

double UTILS::max(double a, double b)
{
    return (a>b)?a:b;
}

double UTILS::min(double a, double b)
{
    return (a<b)?a:b;
}

double UTILS::max(double a, double b, double c)
{
    return UTILS::max(UTILS::max(a,b),c);
}

simplePoint3 UTILS::vec3_to_simplePoint(const QVector3D& t)
{
    simplePoint3 tmp;
    tmp.x = t.x();
    tmp.y = t.y();
    tmp.z = t.z();
    return tmp;
}

QVector3D UTILS::simplePoint_to_Vec3(const simplePoint3& t)
{
    return QVector3D(t.x, t.y,t.z);
}

bool UTILS::IntersectTriangle(QVector3D orig, QVector3D dir,
                              QVector3D v0, QVector3D v1, QVector3D v2,
                              QVector3D& intersectedPoint)
{
    // E1
    QVector3D E1 = v1 - v0;
    QVector3D E2 = v2 - v0;
    QVector3D P = QVector3D::crossProduct(dir,E2);

    float det = QVector3D::dotProduct(E1,P);

    float u,v,t;

    // 保证det > 0, 响应的修改T。
    QVector3D T;
    if (det > 0)
    {
        T = orig - v0;
    }
    else
    {
        T = v0 - orig;
        det = -det;
    }

    // 如果determinant接近0，也就是有向体积接近0，就说明射线和E1&E2平面共面。
    if (det < 0.0001f)
    {
        return false;
    }

    u = QVector3D::dotProduct(T, P);
    if (u < 0.0f || u > det)
    {
        return false;
    }

    // Q
    QVector3D Q = QVector3D::crossProduct(T, E1);

    v = QVector3D::dotProduct(dir, Q);
    if (v < 0.0f || u + v > det)
    {
        return false;
    }

    t = QVector3D::dotProduct(E2, Q);

    float invD = 1.0f / det;
    t *= invD;
    u *= invD;
    v *= invD;

    intersectedPoint = u*(v1-v0)+v*(v2-v0)+v0;

    return true;
}
