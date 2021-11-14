//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_FIELD_H
#define BUGSINVATION_FIELD_H

#include "Ogre.h"
#include "PhysicBase.h"

using namespace Ogre;

class Field : public PhysicBase {
public:
    void createField(SceneManager *scnMgr, Light *light);

    void render(const Ogre::FrameEvent &evt);

    void createPhysicEntity(PhysicsWorld *world, PhysicsCommon *physicsCommon) override;

private:
    SceneNode *terrainNode;
    Ogre::Entity *terrainEntity;
    RigidBody *fieldBody;
    float heightValues[100];

    SceneManager *scnMgr;

};

#endif //BUGSINVATION_FIELD_H
