//
// Created by guille on 13.11.21.
//

#include "../inc/Game.h"

Game::Game() : OgreBites::ApplicationContext("OgreTutorialApp") {
}

bool Game::keyPressed(const OgreBites::KeyboardEvent &evt) {
//    SceneNode *node = camNode;
    Real moveDistance = 10;
    switch (evt.keysym.sym) {
        case OgreBites::SDLK_ESCAPE:
            getRoot()->queueEndRendering();
            break;
        case OgreBites::SDLK_LEFT:
            tank->moveLeft();
            break;
        case OgreBites::SDLK_RIGHT:
            tank->moveRight();
            break;
        case OgreBites::SDLK_UP:
            tank->moveForward();
            break;
        case OgreBites::SDLK_DOWN:
            tank->moveBack();
            break;
        default:
            break;
    }
//    Ogre::Vector3 pos = node->getPosition();
//    printf("position: %f, %f, %f\n", pos.x, pos.y, pos.z);
    return true;
}

void Game::setup() {
    OgreBites::ApplicationContext::setup();

    addInputListener(this);

    scnMgr = getRoot()->createSceneManager();
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    createLight(scnMgr);
    createCamera(scnMgr);

    gameField = new Field();
    gameField->createField(scnMgr, light);

    tank = new Tank(scnMgr);

    createPhysicWord();

//    getRoot()->showConfigDialog();
}

void Game::createLight(SceneManager *scnMgr) {
    light = scnMgr->createLight("MainLight");
    light->setType(Light::LT_POINT);
    light->setDiffuseColour(0.5, 0.5, 0.5);
    light->setSpecularColour(ColourValue(0.4, 0.4, 0.4));
    lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 110, 50);
    lightNode->attachObject(light);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
//    physics.getDynamicsWorld()->stepSimulation(evt.timeSinceLastFrame);

    tank->render(evt);
    gameField->render(evt);
    return true;
}

void Game::createCamera(SceneManager *scnMgr) {
    Camera *camera = scnMgr->createCamera("myCam");
    camera->setNearClipDistance(0.1); // specific to this sample
    camera->setFarClipDistance(0); // specific to this sample
    camera->setAutoAspectRatio(true);

    SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 60, 100);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_PARENT);
    camNode->attachObject(camera);

    getRenderWindow()->addViewport(camera);
}

void Game::createPhysicWord() {
    physics.initObjects();

//    gameField->createPhysicEntity(dynamicsWorld);
    tank->createPhysicEntity(&physics);
}
