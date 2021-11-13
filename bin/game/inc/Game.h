//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_GAME_H
#define BUGSINVATION_GAME_H

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "Field.h"
#include "Tanks/Tank.h"

using namespace Ogre;

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

    void createLight(SceneManager *scnMgr);
    void createCamera(SceneManager *scnMgr);
};

#endif //BUGSINVATION_GAME_H
