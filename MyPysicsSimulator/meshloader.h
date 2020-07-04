#ifndef MESHLOADER_H
#define MESHLOADER_H
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include "utils.h"

enum OBJ_TYPE{
    _TRIANGLES = GL_TRIANGLES,
    _QUADS = GL_QUADS,
};

struct GLBuffer
{
    QOpenGLBuffer VBO;
    int vertex_count;

};

struct BBox
{
    QVector3D center;
    double rx,ry,rz;
};

struct BSphere
{
    QVector3D center;
    double r;
};

class MeshLoader
{
public:
    MeshLoader();

    QVector<QVector3D> vertexes;
    QVector<QVector3D> normals;
    QVector<int> findex;

    OBJ_TYPE mesh_type = _TRIANGLES;

    GLBuffer vbo;

    BBox bbox;
    BSphere bsphere;

    void LoadMeshs(const QString& filename, OBJ_TYPE type = _TRIANGLES, double scale=1.0f);
    void RenderMesh(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat);

private:
    void ComputeBoundings();
    void GenerateVBO();
};

#endif // MESHLOADER_H
