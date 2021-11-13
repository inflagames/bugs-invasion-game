//
// Created by guille on 13.11.21.
//

#include "../inc/Game.h"

Game::Game() : OgreBites::ApplicationContext("OgreTutorialApp") {
}

bool Game::keyPressed(const OgreBites::KeyboardEvent &evt) {
    SceneNode *node = camNode;
    Real moveDistance = 10;
    switch (evt.keysym.sym) {
        case OgreBites::SDLK_ESCAPE:
            getRoot()->queueEndRendering();
            break;
        case OgreBites::SDLK_LEFT:
            node->setPosition(
                    Vector3(node->getPosition().x - moveDistance, node->getPosition().y, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(-2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_RIGHT:
            node->setPosition(
                    Vector3(node->getPosition().x + moveDistance, node->getPosition().y, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_DOWN:
            node->setPosition(
                    Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z - moveDistance));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_UP:
            node->setPosition(
                    Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z + moveDistance));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_SPACE:
            node->setPosition(
                    Vector3(node->getPosition().x, node->getPosition().y + moveDistance, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::KMOD_CTRL:
            node->setPosition(
                    Vector3(node->getPosition().x, node->getPosition().y - moveDistance, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        default:
            break;
    }
    Vector3 pos = node->getPosition();
//    printf("position: %f, %f, %f\n", pos.x, pos.y, pos.z);
    return true;
}

void Game::setup() {
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Root *root = getRoot();
    SceneManager *scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator *shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
    shaderGen->addSceneManager(scnMgr);

    // without light we would just get a black screen
    Light *light = scnMgr->createLight("MainLight");
    light->setType(Light::LT_SPOTLIGHT);
    light->setDiffuseColour(ColourValue::White);
    light->setSpecularColour(ColourValue(0.4, 0.4, 0.4));
    SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 3000, 0);
    lightNode->attachObject(light);

    // also need to tell where we are
    camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 1500, 0);
    camNode->lookAt(Vector3(0, 0, -1000), Node::TS_WORLD);

    // create the camera
    Camera *cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(0.1); // specific to this sample
    cam->setFarClipDistance(0); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
//    Entity* ent = scnMgr->createEntity("tank.mesh");
//    node = scnMgr->getRootSceneNode()->createChildSceneNode();
//    node->attachObject(ent);
//    node->rotate(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3(1,0,0)), Ogre::Node::TS_LOCAL);

//    AnimationStateSet* some = ent->getAllAnimationStates();
//    if (some == nullptr) {
//        printf("-----IS NULL-----\n");
//    } else {
//        printf("-----WITH ANIMATION-----\n");
//        AnimationStateIterator asi = some->getAnimationStateIterator();
//        int c = 0;
//        while(asi.hasMoreElements()) {
//            printf("%s\n", asi.current()->first.c_str());
//            asi.moveNext();
//            c++;
//        }
//        printf("%d\n", c);
//    }

//    as = ent->getAnimationState("rotate_cannon");
//    as->setWeight(1);
//    as->setTimePosition(0);
//    as->setLoop(true);
//    as->setEnabled(true);

    gameField.createField(scnMgr, light);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
//    Real time = evt.timeSinceLastFrame;
//    as->addTime(time);

//    if (terrainGroup->isDerivedDataUpdateInProgress()) {
//        mTrayMgr->moveWidgetToTray(mInfoLabel, TL_TOP, 0);
//        mInfoLabel->show();
//        if (mTerrainsImported)
//        {
//            mInfoLabel->setCaption("Building terrain, please wait...");
//        }
//        else
//        {
//            mInfoLabel->setCaption("Updating textures, patience...");
//        }
//    } else {
//        mTrayMgr->removeWidgetFromTray(mInfoLabel);
//        mInfoLabel->hide();
//    }
    return true;
}