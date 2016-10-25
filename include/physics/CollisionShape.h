#pragma once
#include <graphics/Model.h>

class CollisionShape {
public:
    CollisionShape(btCollisionShape* shape)
        : mShape(shape)
    {}
    CollisionShape(const std::string& path);

    virtual ~CollisionShape() {
        if (mShape) {
            delete mShape;
        }
    }

    btCollisionShape* getBullet() const { return mShape; }

private:
    btCollisionShape* mShape;
};

