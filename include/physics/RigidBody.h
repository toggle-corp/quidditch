#pragma once
#include <physics/CollisionShape.h>
#include <physics/PhysicsWorld.h>
#include <graphics/Model.h>

class RigidBody : public btMotionState {
public:
    struct ConstructionInfo {
        float mass;
        std::shared_ptr<CollisionShape> collisionShape;
        glm::vec3 position;
        glm::quat rotation;

        ConstructionInfo(
            float mass, std::shared_ptr<CollisionShape> collisionShape,
            const glm::vec3& position = glm::vec3(0, 0, 0),
            const glm::quat& rotation = glm::quat(1, 0, 0, 0)
        ) : mass(mass), collisionShape(collisionShape),
            position(position), rotation(rotation)
        {}
    };

    RigidBody(const ConstructionInfo& constructionInfo,
              std::shared_ptr<Model> model = std::shared_ptr<Model>());

    virtual ~RigidBody() {
        if (mRigidBody) {
            if (mWorld)
                mWorld->getBullet()->removeRigidBody(mRigidBody);
            delete mRigidBody;
        }
    }

    void addToWorld(std::shared_ptr<PhysicsWorld> world) {
        mWorld = world;
        if (mWorld && mRigidBody)
            mWorld->getBullet()->addRigidBody(mRigidBody);
    }

    btRigidBody* getBullet() const { return mRigidBody; }

protected:
    virtual void getWorldTransform(btTransform& worldTrans) const;
    virtual void setWorldTransform(const btTransform& worldTrans);

    btRigidBody* mRigidBody;
    std::shared_ptr<Model> mModel;
    std::shared_ptr<PhysicsWorld> mWorld;

    glm::mat4 mTransformation;
};