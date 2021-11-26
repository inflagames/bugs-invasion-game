//
// Created by guille on 25.11.21.
//

#include "../inc/Physics.h"

void Physics::initObjects() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

btDiscreteDynamicsWorld *Physics::getDynamicsWorld() const {
    return dynamicsWorld;
}
