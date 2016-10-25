#include <stdinc.h>
#include <physics/RigidBody.h>


RigidBody::RigidBody(const RigidBody::ConstructionInfo& info,
                      std::shared_ptr<Model> model)
    : mModel(model)
{
    // Calculate inertia
    btVector3 inertia(0,0,0);
    info.collisionShape->getBullet()->calculateLocalInertia(info.mass, inertia);

    // Create bullet construction info
    btRigidBody::btRigidBodyConstructionInfo
        cInfo(info.mass, this, info.collisionShape->getBullet(),
              inertia);

    // Create the rigid body
    mRigidBody = new btRigidBody(cInfo);
    mRigidBody->setUserPointer(this);

    // Calculate initial transformation
    mTransformation = glm::translate(glm::mat4(), info.position)
        * glm::mat4_cast(info.rotation);
}

void RigidBody::getWorldTransform(btTransform& worldTrans) const {
    worldTrans.setFromOpenGLMatrix(glm::value_ptr(mTransformation));
}

void RigidBody::setWorldTransform(const btTransform& worldTrans) {
    worldTrans.getOpenGLMatrix(glm::value_ptr(mTransformation));
}