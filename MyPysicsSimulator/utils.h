#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <QTimer>
#include <QTime>
#include <QVector3D>
#include <GL/gl.h>
#include <GL/glu.h>

#define VERTEX_ATTRIBUTE  0
#define COLOUR_ATTRIBUTE  1
#define NORMAL_ATTRIBUTE  2
#define TEXTURE_ATTRIBUTE 3

struct simplePoint3;

namespace UTILS {    // 定义一些辅助函数

    double max(double a, double b);

    double min(double a, double b);

    double max(double a, double b, double c);

    simplePoint3 vec3_to_simplePoint(const QVector3D& t);
    QVector3D simplePoint_to_Vec3(const simplePoint3& t);

    bool IntersectTriangle(QVector3D orig, QVector3D dir,
            QVector3D v0, QVector3D v1, QVector3D v2,
            QVector3D &intersectedPoint);
}

struct simplePoint3
{
    double x,y,z;
    const static int dimension = 3;
    double getDimension(int dim) const
    {
        switch(dim)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: return std::numeric_limits<double>::quiet_NaN();
        }
    }
};


#endif // UTILS_H
