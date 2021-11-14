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
                    Ogre::Vector3(node->getPosition().x - moveDistance, node->getPosition().y, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(-2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_RIGHT:
            node->setPosition(
                    Ogre::Vector3(node->getPosition().x + moveDistance, node->getPosition().y, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
//        case OgreBites::SDLK_DOWN:
//            node->setPosition(
//                    Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z - moveDistance));
////            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
//            break;
//        case OgreBites::SDLK_UP:
//            node->setPosition(
//                    Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z + moveDistance));
////            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
//            break;
        case OgreBites::SDLK_UP:
            node->setPosition(
                    Ogre::Vector3(node->getPosition().x, node->getPosition().y + moveDistance, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(1,0,0)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_DOWN:
            node->setPosition(
                    Ogre::Vector3(node->getPosition().x, node->getPosition().y - moveDistance, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(-1,0,0)), Ogre::Node::TS_LOCAL);
            break;
        default:
            break;
    }
    Ogre::Vector3 pos = node->getPosition();
//    printf("position: %f, %f, %f\n", pos.x, pos.y, pos.z);
    return true;
}

void Game::setup() {
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    scnMgr = getRoot()->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator *shaderGen = RTShader::ShaderGenerator::getSingletonPtr();
    shaderGen->addSceneManager(scnMgr);

    createLight(scnMgr);
    createCamera(scnMgr);

    gameField = new Field();
    gameField->createField(scnMgr, light);

    tank = new Tank(scnMgr, camNode);

    createPhysicWord();
}

void Game::createLight(SceneManager *scnMgr) {
    light = scnMgr->createLight("MainLight");
    light->setType(Light::LT_POINT);
    light->setDiffuseColour(ColourValue::White);
    light->setSpecularColour(ColourValue(0.4, 0.4, 0.4));
    lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 110, 15);
    lightNode->attachObject(light);
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    physicsWorld->update(evt.timeSinceLastFrame);
    tank->render(evt);
    gameField->render(evt);
    return true;
}

void Game::createCamera(SceneManager *scnMgr) {
    Camera *camera = scnMgr->createCamera("myCam");
    camera->setNearClipDistance(0.1); // specific to this sample
    camera->setFarClipDistance(0); // specific to this sample
    camera->setAutoAspectRatio(true);

    camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 15, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_PARENT);
    camNode->attachObject(camera);

    getRenderWindow()->addViewport(camera);
}

void Game::createPhysicWord() {
    physicsWorld = physicsCommon.createPhysicsWorld();

    gameField->createPhysicEntity(physicsWorld, &physicsCommon);
    tank->createPhysicEntity(physicsWorld, &physicsCommon);
}
