//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_GAME_H
#define BUGSINVATION_GAME_H

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "Field.h"
#include <reactphysics3d/reactphysics3d.h>
#include "Tanks/Tank.h"

using namespace Ogre;
using namespace reactphysics3d;

class Game : public OgreBites::ApplicationContext, public OgreBites::InputListener {
public:
    Game();

    void setup();

    bool keyPressed(const OgreBites::KeyboardEvent &evt);

    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

private:
    SceneManager *scnMgr;
    SceneNode *camNode;
    SceneNode *lightNode;
    Light *light;
    Field *gameField;
    Tank *tank;

    PhysicsCommon physicsCommon;
    PhysicsWorld *physicsWorld;

    void createLight(SceneManager *scnMgr);
    void createCamera(SceneManager *scnMgr);
    void createPhysicWord();
};

#endif //BUGSINVATION_GAME_H
