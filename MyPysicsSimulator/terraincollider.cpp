#include "terraincollider.h"
#include <vector>

TerrainCollider m_terrain;

TerrainCollider::TerrainCollider()
{

}

void TerrainCollider::LoadTerrainMesh(const QString &filename, OBJ_TYPE type, double scale)
{
    this->LoadMeshs(filename, type,scale);  // 加载模型

    this->BuildMeshCollider();
}

void TerrainCollider::BuildMeshCollider()
{
    qDebug()<<"build"<<findex.size();
    for(int m=0; m<findex.size(); m+=2)
    {
        int vid = findex[m];
        int nid = findex[m+1];
        simplePoint3 tmp = UTILS::vec3_to_simplePoint(vertexes[vid]);

        collide_vertexes.push_back(tmp);
        collide_normals.push_back(normals[nid].normalized());
    }

    index.buildTree(collide_vertexes);
    qDebug()<<"done";
}


bool TerrainCollider::Collide(QVector3D pos,QVector3D dir, double radius, QVector3D& mesh_normal)
{
    // input : (pos, dir, radius): target bsphere.
    // return: mesh_normal
    // kd tree (radius search....)
    auto closeNodes = index.getPointsWithinCube(UTILS::vec3_to_simplePoint(pos),
                                                radius*5.);
    double mindist = INT_MAX;
    int minID = -1;
    QVector3D intersectedPoint;

    // 三角面片和射线的碰撞检测
    for(unsigned int i=0; i<closeNodes.size(); ++i)  // [0],1,2,[3],4,5,[6],
    {
        int id = closeNodes[i];

        int id0 = 3*int(id/3);
        int id1 = id0+1;
        int id2 = id0+2;

        QVector3D v0 = UTILS::simplePoint_to_Vec3(collide_vertexes[id0]);
        QVector3D v1 = UTILS::simplePoint_to_Vec3(collide_vertexes[id1]);
        QVector3D v2 = UTILS::simplePoint_to_Vec3(collide_vertexes[id2]);
        QVector3D _intersectedPoint;

        if(UTILS::IntersectTriangle(pos, dir,v0,v1,v2,_intersectedPoint))  // 发生碰撞
        {
            double dist = _intersectedPoint.distanceToPoint(pos);

            if(dist <= 1.1*radius && dist<mindist)
            {
                mindist = dist;
                minID = id;
                intersectedPoint = _intersectedPoint;
            }
        }
    }

    if(minID == -1)
        return false;

    mesh_normal = collide_normals[minID]; // 碰撞位置处的发现
    if(QVector3D::dotProduct(mesh_normal,dir)<0)
        mesh_normal = -mesh_normal;
    return true;

}
