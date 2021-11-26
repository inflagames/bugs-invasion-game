//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_FIELD_H
#define BUGSINVATION_FIELD_H

#include "Ogre.h"
#include "PhysicBase.h"
#include "btBulletDynamicsCommon.h"

using namespace Ogre;

class Field : public PhysicBase {
public:
    void createField(SceneManager *scnMgrIns, Light *light);

    void render(const Ogre::FrameEvent &evt);

    void createPhysicEntity(Physics *physics) override;

private:
    SceneNode *terrainNode = nullptr;
    Ogre::Entity *terrainEntity = nullptr;
    float heightValues[10000];

    SceneManager *scnMgr = nullptr;

};

#endif //BUGSINVATION_FIELD_H
