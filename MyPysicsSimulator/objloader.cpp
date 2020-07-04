//#include "objloader.h"

//ObjLoader::ObjLoader()
//{

//}

//QPair<float,float> Material::GetCenterX()
//{
//    float max_x = -9999999;
//    float min_x = +9999999;

//    for(unsigned int i=0; i< m_vertices_3.size(); ++i)
//    {
//        max_x = (max_x > m_vertices_3[i].x()) ? max_x : m_vertices_3[i].x();
//        min_x = (min_x < m_vertices_3[i].x()) ? min_x : m_vertices_3[i].x();
//    }

//    for(unsigned int i=0; i< m_vertices_4.size(); ++i)
//    {
//        max_x = (max_x > m_vertices_4[i].x()) ? max_x : m_vertices_4[i].x();
//        min_x = (min_x < m_vertices_4[i].x()) ? min_x : m_vertices_4[i].x();
//    }
//    return QPair<float,float>(max_x, min_x);
//}

//QPair<float,float> Material::GetCenterY()
//{
//    float max_y = -9999999;
//    float min_y = +9999999;

//    for(unsigned int i=0; i< m_vertices_3.size(); ++i)
//    {
//        max_y = (max_y > m_vertices_3[i].y()) ? max_y : m_vertices_3[i].y();
//        min_y = (min_y < m_vertices_3[i].y()) ? min_y : m_vertices_3[i].y();
//    }

//    for(unsigned int i=0; i< m_vertices_4.size(); ++i)
//    {
//        max_y = (max_y > m_vertices_4[i].y()) ? max_y : m_vertices_4[i].y();
//        min_y = (min_y < m_vertices_4[i].y()) ? min_y : m_vertices_4[i].y();
//    }
//    return QPair<float,float>(max_y, min_y);
//}

//QPair<float,float> Material::GetCenterZ()
//{
//    float max_z = -9999999;
//    float min_z = +9999999;

//    for(unsigned int i=0; i< m_vertices_3.size(); ++i)
//    {
//        max_z = (max_z > m_vertices_3[i].z()) ? max_z : m_vertices_3[i].z();
//        min_z = (min_z < m_vertices_3[i].z()) ? min_z : m_vertices_3[i].z();
//    }

//    for(unsigned int i=0; i< m_vertices_4.size(); ++i)
//    {
//        max_z = (max_z > m_vertices_4[i].z()) ? max_z : m_vertices_4[i].z();
//        min_z = (min_z < m_vertices_4[i].z()) ? min_z : m_vertices_4[i].z();
//    }
//    return QPair<float,float>(max_z, min_z);
//}

//void Material::createVBO()
//{
//    if(this->m_VBO_3.isCreated())
//        this->m_VBO_3.release();

//    QVector<GLfloat> data_3;

//    for(unsigned int i=0; i<m_vertices_3.size(); i++)
//    {
//        data_3.push_back(m_vertices_3[i].x());
//        data_3.push_back(m_vertices_3[i].y());
//        data_3.push_back(m_vertices_3[i].z());

//        data_3.push_back(m_normals_3[i].x());
//        data_3.push_back(m_normals_3[i].y());
//        data_3.push_back(m_normals_3[i].z());

//        if(m_isTexturedKa ||m_isTexturedKd)
//        {
//            data_3.push_back(m_texcoords_3[i].x());
//            data_3.push_back(m_texcoords_3[i].y());
//            data_3.push_back(m_texcoords_3[i].z());
//        }
//    }

//    this->m_VBO_3.create();
//    this->m_VBO_3.bind();
//    this->m_VBO_3.allocate(data_3.constData(),data_3.count()*sizeof(GLfloat));

//    if(m_isTexturedKa || m_isTexturedKd)
//        m_vertice_3_count = data_3.size()/9.0;
//    else
//        m_vertice_3_count = data_3.size()/6.0;

//    if(this->m_VBO_4.isCreated())
//        this->m_VBO_4.release();

//    QVector<GLfloat> data_4;

//    for(unsigned int i=0; i<m_vertices_4.size(); i++)
//    {
//        data_4.push_back(m_vertices_4[i].x());
//        data_4.push_back(m_vertices_4[i].y());
//        data_4.push_back(m_vertices_4[i].z());

//        data_4.push_back(m_normals_4[i].x());
//        data_4.push_back(m_normals_4[i].y());
//        data_4.push_back(m_normals_4[i].z());

//        if(m_isTexturedKa ||m_isTexturedKd)
//        {
//            data_4.push_back(m_texcoords_4[i].x());
//            data_4.push_back(m_texcoords_4[i].y());
//            data_4.push_back(m_texcoords_4[i].z());
//        }
//    }

//    this->m_VBO_4.create();
//    this->m_VBO_4.bind();
//    this->m_VBO_4.allocate(data_4.constData(),data_4.count()*sizeof(GLfloat));

//    if(m_isTexturedKa || m_isTexturedKd)
//        m_vertice_4_count = data_4.size()/9.0;
//    else
//        m_vertice_4_count = data_4.size()/6.0;
//}

//void Material::renderVBO(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat)
//{
//#define VERTEX_ATTRIBUTE 0
//#define NORMAL_ATTRIBUTE 1
//#define TEXTURE_ATTRIBUTE 2

//    program->setUniformValue("mat_model",modelMat);
//    program->setUniformValue("isTexturedKa",m_isTexturedKa);
//    program->setUniformValue("isTexturedKd",m_isTexturedKd);
//    program->setUniformValue("ka",this->m_Ka);
//    program->setUniformValue("kd",this->m_Kd);
//    program->setUniformValue("ks",this->m_Ks);
////    program->setUniformValue("textureKa",0);
////    this->m_textureKa->bind();
//    if(m_isTexturedKd)
//    {
//        program->setUniformValue("textureKd",0);
//        this->m_textureKd->bind();
//    }
//    if(m_vertice_4_count >0 && m_VBO_4.isCreated())
//    {
//        this->m_VBO_4.bind();
//        if(m_isTexturedKa || m_isTexturedKd)
//        {
//            program->enableAttributeArray(VERTEX_ATTRIBUTE);
//            program->enableAttributeArray(NORMAL_ATTRIBUTE);
//            program->enableAttributeArray(TEXTURE_ATTRIBUTE);
//            program->setAttributeBuffer(VERTEX_ATTRIBUTE,   GL_FLOAT, 0,                3,9*sizeof(GLfloat));
//            program->setAttributeBuffer(NORMAL_ATTRIBUTE,   GL_FLOAT, 3*sizeof(GLfloat),3,9*sizeof(GLfloat));
//            program->setAttributeBuffer(TEXTURE_ATTRIBUTE,  GL_FLOAT, 6*sizeof(GLfloat),3,9*sizeof(GLfloat));
//        }
//        else
//        {
//            program->enableAttributeArray(VERTEX_ATTRIBUTE);
//            program->enableAttributeArray(NORMAL_ATTRIBUTE);
//            program->setAttributeBuffer(VERTEX_ATTRIBUTE,   GL_FLOAT, 0,                3,6*sizeof(GLfloat));
//            program->setAttributeBuffer(NORMAL_ATTRIBUTE,   GL_FLOAT, 3*sizeof(GLfloat),3,6*sizeof(GLfloat));
//        }

//        glDrawArrays(GL_QUADS,0,this->m_vertice_4_count);
//    }
//    if(m_vertice_3_count >0 && m_VBO_3.isCreated())
//    {
//        this->m_VBO_3.bind();
//        if(m_isTexturedKa || m_isTexturedKd)
//        {
//            program->enableAttributeArray(VERTEX_ATTRIBUTE);
//            program->enableAttributeArray(NORMAL_ATTRIBUTE);
//            program->enableAttributeArray(TEXTURE_ATTRIBUTE);
//            program->setAttributeBuffer(VERTEX_ATTRIBUTE,   GL_FLOAT, 0,                3,9*sizeof(GLfloat));
//            program->setAttributeBuffer(NORMAL_ATTRIBUTE,   GL_FLOAT, 3*sizeof(GLfloat),3,9*sizeof(GLfloat));
//            program->setAttributeBuffer(TEXTURE_ATTRIBUTE,  GL_FLOAT, 6*sizeof(GLfloat),3,9*sizeof(GLfloat));
//        }
//        else
//        {
//            program->enableAttributeArray(VERTEX_ATTRIBUTE);
//            program->enableAttributeArray(NORMAL_ATTRIBUTE);
//            program->setAttributeBuffer(VERTEX_ATTRIBUTE,   GL_FLOAT, 0,                3,6*sizeof(GLfloat));
//            program->setAttributeBuffer(NORMAL_ATTRIBUTE,   GL_FLOAT, 3*sizeof(GLfloat),3,6*sizeof(GLfloat));
//        }

//        glDrawArrays(GL_TRIANGLES,0,this->m_vertice_3_count);
//    }
//}

//void ObjLoader::renderObj(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat)
//{
//    for(unsigned int i=0; i<m_materials.size(); i++)
//        m_materials[i].renderVBO(program,modelMat);
//}

//float ObjLoader::loadObjFromFile(const QString& pathObj)
//{
//    clearAll();

//    QString pathMtl = QFileInfo(pathObj).absolutePath() + "/" +QFileInfo(pathObj).baseName() + ".mtl";

//    qDebug()<<"Loading:";
//    qDebug()<<pathMtl;
//    qDebug()<<pathObj;

//    QFile fileMtl(pathMtl);

//    if(!fileMtl.open(QIODevice::ReadOnly))
//        return 1;
//    qDebug()<<"加载";

//    QTextStream tsMtl(&fileMtl);

//    m_materials.clear();

//    while(!tsMtl.atEnd())
//    {
//        QStringList line = tsMtl.readLine().split(QRegExp("\\s+"),QString::SkipEmptyParts);

//        //qDebug()<<line;

//        if(line.isEmpty() || line[0] == "#")
//            continue;

//        if(line[0] == "newmtl")
//            m_materials.push_back(Material(line[1]));

//        if(line[0] == "Ka")
//        {
//            Material& mat = m_materials.back();
//            mat.m_Ka = QVector3D(line[1].toFloat(),line[2].toFloat(),line[3].toFloat());
//        }
//        if(line[0] == "Kd")
//        {
//            Material& mat = m_materials.back();
//            mat.m_Kd = QVector3D(line[1].toFloat(),line[2].toFloat(),line[3].toFloat());
//        }
//        if(line[0] == "Ks")
//        {
//            Material& mat = m_materials.back();
//            mat.m_Ks = QVector3D(line[1].toFloat(),line[2].toFloat(),line[3].toFloat());
//        }
//        if(line[0] == "map_Ka")
//        {
//            Material& mat = m_materials.back();
//            mat.m_isTexturedKa = true;
//            mat.m_TextureKaName = line[1];
//        }
//        if(line[0] == "map_Kd")
//        {
//            Material& mat = m_materials.back();
//            mat.m_isTexturedKd = true;
//            mat.m_TextureKdName = line[1];
//        }
//    }

//    qDebug()<<"Material Count:"<<m_materials.size();

//    QVector<QVector3D> vec;
//    QVector<QVector3D> nor;
//    QVector<QVector3D> tex;

//    QFile fileObj(pathObj);

//    if(!fileObj.open(QIODevice::ReadOnly))
//        return 1;

//    QTextStream tsObj(&fileObj);

//    Material* curMat = NULL;

//    float maxDistance = 0;

//    while(!tsObj.atEnd())
//    {
//        QStringList line = tsObj.readLine().split(QRegExp("\\s+"),QString::SkipEmptyParts);

//        if(line.isEmpty() || line[0] == "#")
//            continue;

//        if(line[0] == "v")
//        {
//            vec.push_back(QVector3D(line[1].toFloat(),line[2].toFloat(),line[3].toFloat()));

//            vec.back() = vec.back()*0.1;
//            // update max distance
//            if(fabs(vec.back().x()) > maxDistance)
//                maxDistance = fabs(vec.back().x());
//            if(fabs(vec.back().y()) > maxDistance)
//                maxDistance = fabs(vec.back().y());
//            if(fabs(vec.back().z()) > maxDistance)
//                maxDistance = fabs(vec.back().z());
//        }
//        if(line[0] == "vn")
//            nor.push_back(QVector3D(line[1].toFloat(),line[2].toFloat(),line[3].toFloat()));
//        if(line[0] == "vt")
//            tex.push_back(QVector3D(line[1].toFloat(),-line[2].toFloat(),0.0f));

//        if(line[0] == "f" && curMat)
//        {
//            if(line.size() == 4) // 3 vertices of each face
//            {
//                for(unsigned int i=1; i<line.size(); i++)
//                {
//                    QStringList tmp = line[i].split("/",QString::SkipEmptyParts);

//                    curMat->m_vertices_3.push_back(vec[tmp[0].toInt()-1]);
//                    curMat->m_texcoords_3.push_back(tex[tmp[1].toInt()-1]);
//                    curMat->m_normals_3.push_back(nor[tmp[2].toInt()-1]);

//                    //qDebug()<<tmp;
//                }
//            }
//            if(line.size() == 5) // 4 vertices of each face
//            {
//                for(unsigned int i=1; i<line.size(); i++)
//                {
//                    QStringList tmp = line[i].split("/",QString::SkipEmptyParts);

//                    curMat->m_vertices_4.push_back(vec[tmp[0].toInt()-1]);
//                    curMat->m_texcoords_4.push_back(tex[tmp[1].toInt()-1]);
//                    curMat->m_normals_4.push_back(nor[tmp[2].toInt()-1]);
//                }
//            }
//        }

//        if(line[0] == "usemtl")
//        {

//            for(unsigned int i=0; i<m_materials.size(); i++)
//            {
//                if(line[1] == m_materials[i].m_mtlName)
//                {
//                    curMat = &m_materials[i];
//                    break;
//                }
//            }
//        }
//    }

//    vec.clear();
//    tex.clear();
//    nor.clear();

//    qDebug()<<"Load obj Done!";

//    float max_y = -99999999,min_y=+99999999;
//    float max_x = -99999999,min_x=+99999999;
//    float max_z = -99999999,min_z=+99999999;
//    for(unsigned int i=0 ; i<m_materials.size(); ++i)
//    {
//        QPair<float,float> pair = m_materials[i].GetCenterY();
//        max_y = pair.first > max_y ? pair.first : max_y;
//        min_y = pair.second < min_y ? pair.second : min_y;

//        QPair<float,float> pairX = m_materials[i].GetCenterX();
//        max_x = pairX.first > max_x ? pairX.first : max_x;
//        min_x = pairX.second < min_x ? pairX.second : min_x;

//        QPair<float,float> pairZ = m_materials[i].GetCenterZ();
//        max_z = pairZ.first > max_z ? pairZ.first : max_z;
//        min_z = pairZ.second < min_z ? pairZ.second : min_z;
//    }
//    float centerY = (max_y + min_y)/ 2.0f;
//    float centerX = (max_x + min_x)/ 2.0f;
//    float centerZ = (max_z + min_z)/ 2.0f;
//    qDebug()<<max_y<<min_y<<centerY;
//    qDebug()<<max_x<<min_x<<centerX;

//    for(unsigned int i=0; i<m_materials.size(); i++)
//    {

//        for(unsigned int k = 0; k <m_materials[i].m_vertices_3.size(); ++k)
//        {

//            m_materials[i].m_vertices_3[k].setY(
//                        m_materials[i].m_vertices_3[k].y() - centerY
//                        );

//            m_materials[i].m_vertices_3[k].setX(
//                        m_materials[i].m_vertices_3[k].x() - centerX
//                        );
//            m_materials[i].m_vertices_3[k].setZ(
//                        m_materials[i].m_vertices_3[k].z() - centerZ
//                        );
//        }
//        for(unsigned int k = 0; k <m_materials[i].m_vertices_4.size(); ++k)
//        {
//            m_materials[i].m_vertices_4[k].setY(
//                        m_materials[i].m_vertices_4[k].y() - centerY
//                        );

//            m_materials[i].m_vertices_4[k].setX(
//                        m_materials[i].m_vertices_4[k].x() - centerX
//                        );
//            m_materials[i].m_vertices_4[k].setZ(
//                        m_materials[i].m_vertices_4[k].z() - centerZ
//                        );
//        }

//        m_materials[i].createVBO();

//        // Load textures of each material;
//        if(m_materials[i].m_isTexturedKa)
//        {

//            QImage img(QFileInfo(pathObj).absolutePath() +"/" + m_materials[i].m_TextureKaName);
//            m_materials[i].m_textureKa = new QOpenGLTexture(img);
//            m_materials[i].m_textureKa->setMinificationFilter(QOpenGLTexture::Nearest);
//            m_materials[i].m_textureKa->setMagnificationFilter(QOpenGLTexture::Linear);
//        }
//        if(m_materials[i].m_isTexturedKd)
//        {
//            QImage img(QFileInfo(pathObj).absolutePath() +"/" + m_materials[i].m_TextureKdName);
//            m_materials[i].m_textureKd = new QOpenGLTexture(img);
//            m_materials[i].m_textureKd->setMinificationFilter(QOpenGLTexture::Nearest);
//            m_materials[i].m_textureKd->setMagnificationFilter(QOpenGLTexture::Linear);
//        }
//    }

//    qDebug()<<"Transfer Finished!";

//    return maxDistance;
//}

//void ObjLoader::clearAll()
//{
//    for(unsigned int i=0; i<m_materials.size(); i++)
//    {
//        m_materials[i].m_VBO_3.release();
//        m_materials[i].m_VBO_4.release();

//        if(m_materials[i].m_isTexturedKa)
//        {
//            m_materials[i].m_textureKa->release();
//            delete m_materials[i].m_textureKa;
//        }
//        if(m_materials[i].m_isTexturedKd)
//        {
//            m_materials[i].m_textureKd->release();
//            delete m_materials[i].m_textureKd;
//        }

//        m_materials[i].m_vertices_3.clear();
//        m_materials[i].m_vertices_4.clear();
//        m_materials[i].m_normals_3.clear();
//        m_materials[i].m_normals_4.clear();
//        m_materials[i].m_texcoords_3.clear();
//        m_materials[i].m_texcoords_4.clear();
//    }

//    m_materials.clear();
//}
