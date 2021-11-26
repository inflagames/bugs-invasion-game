//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_PHYSICBASE_H
#define BUGSINVATION_PHYSICBASE_H

#include "btBulletDynamicsCommon.h"
#include "Physics.h"

class PhysicBase {
public:
    virtual void createPhysicEntity(Physics *physics) = 0;
};

#endif //BUGSINVATION_PHYSICBASE_H
