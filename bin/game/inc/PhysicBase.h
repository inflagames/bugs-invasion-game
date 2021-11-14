//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_PHYSICBASE_H
#define BUGSINVATION_PHYSICBASE_H

#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicBase {
public:
    virtual void createPhysicEntity(PhysicsWorld *world, PhysicsCommon *physicsCommon) = 0;
};

#endif //BUGSINVATION_PHYSICBASE_H
