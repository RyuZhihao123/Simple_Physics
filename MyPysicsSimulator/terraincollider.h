#ifndef TERRAINCOLLIDER_H
#define TERRAINCOLLIDER_H
#include "meshloader.h"
#include "kdtree.h"
class TerrainCollider : public MeshLoader
{
public:
    TerrainCollider();

    void LoadTerrainMesh(const QString& filename, OBJ_TYPE type = _TRIANGLES, double scale=1.0f);

    void BuildMeshCollider();

    // kd树用的碰撞检测的顶点
    std::vector<simplePoint3> collide_vertexes;
    QVector<QVector3D> collide_normals;
    KDTree<simplePoint3> index;       // kd tree

    bool Collide(QVector3D pos, QVector3D dir, double radius, QVector3D &mesh_normal);

};

extern TerrainCollider m_terrain;

#endif // TERRAINCOLLIDER_H
