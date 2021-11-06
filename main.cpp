// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "Ogre.h"
#include "OgreApplicationContext.h"

using namespace Ogre;

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    MyTestApp();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

//! [constructor]
MyTestApp::MyTestApp() : OgreBites::ApplicationContext("OgreTutorialApp")
{
}
//! [constructor]

SceneNode* node;

//! [key_handler]
bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    } else if (evt.keysym.sym == OgreBites::SDLK_LEFT) {
        node->rotate(Ogre::Quaternion(Ogre::Degree(-2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
    } else if (evt.keysym.sym == OgreBites::SDLK_RIGHT) {
        node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
    }
    return true;
}
//! [key_handler]

//! [setup]
void MyTestApp::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    // also need to tell where we are
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 15, 15);
    camNode->lookAt(Vector3(0, 0, 0), Node::TS_PARENT);

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
    Entity* ent = scnMgr->createEntity("tank.mesh");
    node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    node->rotate(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3(1,0,0)), Ogre::Node::TS_LOCAL);
}
//! [setup]

//! [main]
int main(int argc, char *argv[])
{
    MyTestApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
//! [main]
