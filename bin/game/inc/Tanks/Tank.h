//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_TANK_H
#define BUGSINVATION_TANK_H

#include "Ogre.h"
#include "../PhysicBase.h"
#include "../Utils.h"

using namespace Ogre;

class Tank : public PhysicBase {
public:
    Tank(SceneManager *scnMgr, SceneNode *camNode);

    void rotateCannon(Real angle);

    void render(const Ogre::FrameEvent &evt);

    void createPhysicEntity(PhysicsWorld *world, PhysicsCommon *physicsCommon) override;

private:
    SceneNode *camNode;
    SceneNode *tankNode;
    Ogre::Entity *tankEntity;
    AnimationState *tankAnimationEntity;
    RigidBody *tankPhysicBody;
};

#endif //BUGSINVATION_TANK_H
