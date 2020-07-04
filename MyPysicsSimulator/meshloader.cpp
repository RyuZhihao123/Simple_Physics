#include "meshloader.h"
#include <limits>
MeshLoader::MeshLoader()
{

}


void MeshLoader::LoadMeshs(const QString &filename, OBJ_TYPE type, double scale)
{
    this->mesh_type = type;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QTextStream ts(&file);


    while(!ts.atEnd())
    {
        QStringList line = ts.readLine().split(QRegExp("\\s+"));

        if(line[0] == "v")
        {
            QVector3D pts(line[1].toFloat(),line[2].toFloat(),line[3].toFloat());
            pts *= scale;
            vertexes.append(pts);
        }
        if(line[0] == "vn")
        {
            normals.append(QVector3D(line[1].toDouble(),line[2].toDouble(),line[3].toDouble()));
        }
        if(line[0] == "f")
        {
            for(int i=1; i<line.size(); ++i)
            {
                QStringList cell = line[i].split("/");

                int vid = cell[0].toInt() - 1;
                int nid = cell[2].toInt() - 1;

                // form the GLBuffer's VBO;
                findex.append(vid);
                findex.append(nid);
            }
        }
    }

    ComputeBoundings();
    GenerateVBO();

    qDebug()<<"[Load model]"<<filename;
}


void MeshLoader::ComputeBoundings()
{
    double xmin,ymin,zmin,xmax,ymax,zmax;
    xmin = ymin = zmin = +INT_MAX;
    xmax = ymax = zmax = -INT_MAX;

    for(int i=0; i<vertexes.size(); ++i)
    {
        QVector3D pt = vertexes[i];

        xmin = UTILS::min(xmin, pt.x());
        ymin = UTILS::min(ymin, pt.y());
        zmin = UTILS::min(zmin, pt.z());

        xmax = UTILS::max(xmax, pt.x());
        ymax = UTILS::max(ymax, pt.y());
        zmax = UTILS::max(zmax, pt.z());
    }

    QVector3D c((xmin+xmax)/2.0, (ymin+ymax)/2.0, (zmin+zmax)/2.0);

    for(int i=0; i<vertexes.size(); ++i)
    {
        vertexes[i] = vertexes[i] - c;
    }


    this->bbox.center = this->bsphere.center = QVector3D(0,0,0);
    this->bbox.rx = (xmax-xmin)/2.;
    this->bbox.ry = (ymax-ymin)/2.;
    this->bbox.rz = (zmax-zmin)/2.;

    this->bsphere.r = UTILS::max(bbox.rx,bbox.ry,bbox.rz);
}

void MeshLoader::GenerateVBO()
{
    if(this->vbo.VBO.isCreated())
        vbo.VBO.release();

    QVector<GLfloat> data;

    for(int i=0; i<findex.size(); i+=2)  // v, vn
    {
        int vid = findex[i];
        int nid = findex[i+1];

        data.append(vertexes[vid].x());
        data.append(vertexes[vid].y());
        data.append(vertexes[vid].z());

        data.append(normals[nid].x());
        data.append(normals[nid].y());
        data.append(normals[nid].z());
    }

    vbo.VBO.create();
    vbo.VBO.bind();
    vbo.VBO.allocate(data.constData(),data.count()*sizeof(GLfloat));

    vbo.vertex_count = data.size()/6;
}

void MeshLoader::RenderMesh(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat)
{
    if(this->vbo.vertex_count <=0 ||!this->vbo.VBO.isCreated())
        return;

    program->setUniformValue("mat_model",modelMat);

    vbo.VBO.bind();


    program->enableAttributeArray(VERTEX_ATTRIBUTE);
    program->enableAttributeArray(NORMAL_ATTRIBUTE);

    program->setAttributeBuffer(VERTEX_ATTRIBUTE,   GL_FLOAT, 0,                3,6*sizeof(GLfloat));
    program->setAttributeBuffer(NORMAL_ATTRIBUTE,   GL_FLOAT, 3*sizeof(GLfloat),3,6*sizeof(GLfloat));


    glDrawArrays(mesh_type,0,this->vbo.vertex_count);
}
