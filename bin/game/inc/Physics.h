//
// Created by guille on 25.11.21.
//

#ifndef BUGSINVATION_PHYSICS_H
#define BUGSINVATION_PHYSICS_H

#include <vector>
#include <map>
#include <string>
#include "btBulletDynamicsCommon.h"
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>

class Physics {
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    std::vector<btCollisionShape *> collisionShapes;
    std::map<std::string, btRigidBody *> physicsAccessors;
public:
    void initObjects();

    btDiscreteDynamicsWorld *getDynamicsWorld() const;
};

#endif //BUGSINVATION_PHYSICS_H
