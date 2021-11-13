//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_TANK_H
#define BUGSINVATION_TANK_H

#include "Ogre.h"

using namespace Ogre;

class Tank {
public:
    Tank(SceneManager *scnMgr, SceneNode *camNode);
    void rotateCannon(Real angle);
    void render(const Ogre::FrameEvent &evt);

private:
    SceneNode *camNode;
    SceneNode *tankNode;
    AnimationState *tankAnimationEntity;
};

#endif //BUGSINVATION_TANK_H
