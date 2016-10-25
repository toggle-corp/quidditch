#pragma once

class PhysicsWorld {
public:
    PhysicsWorld();
    virtual ~PhysicsWorld();

    btDiscreteDynamicsWorld* getBullet() const { return mDynamicsWorld; }

    void step(double dt) { mDynamicsWorld->stepSimulation(dt); } 

private:
    btBroadphaseInterface* mBroadphase;
    btDefaultCollisionConfiguration* mCollisionConfiguration;
    btCollisionDispatcher* mDispatcher;
    btSequentialImpulseConstraintSolver* mSolver;
    btDiscreteDynamicsWorld* mDynamicsWorld;
};