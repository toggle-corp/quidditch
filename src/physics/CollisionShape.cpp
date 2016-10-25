#include <stdinc.h>
#include <physics/CollisionShape.h>
#include <BulletWorldImporter/btBulletWorldImporter.h>


CollisionShape::CollisionShape(const std::string& path)
{
    btBulletWorldImporter importer;
    importer.loadFile(path.c_str());
    mShape = importer.getCollisionShapeByIndex(0);
}