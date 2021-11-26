//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_TANK_H
#define BUGSINVATION_TANK_H

#include "Ogre.h"
#include "../PhysicBase.h"
#include "../Utils.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "../Physics.h"

using namespace Ogre;

class Tank : public PhysicBase {
public:
    Tank(SceneManager *scnMgr);

    void rotateCannon(Real angle);

    void render(const Ogre::FrameEvent &evt);

    void createPhysicEntity(Physics *physics) override;

    void moveForward();
    void moveBack();
    void moveLeft();
    void moveRight();
private:
    SceneNode *tankNode = nullptr;
    Ogre::Entity *tankEntity = nullptr;
    AnimationState *tankAnimationEntity = nullptr;
};

#endif //BUGSINVATION_TANK_H
