#include <stdinc.h>
#include <physics/PhysicsWorld.h>

PhysicsWorld::PhysicsWorld() {
    // Build the broadphase
    mBroadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    mCollisionConfiguration = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

    // The actual physics solver
    mSolver = new btSequentialImpulseConstraintSolver;

    // The world.
    mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher,
        mBroadphase, mSolver, mCollisionConfiguration);
    mDynamicsWorld->setGravity(btVector3(0, -10, 0));
}

PhysicsWorld::~PhysicsWorld() {
    delete mDynamicsWorld;
    delete mSolver;
    delete mDispatcher;
    delete mCollisionConfiguration;
    delete mBroadphase;
}