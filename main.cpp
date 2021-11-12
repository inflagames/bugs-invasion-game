// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "Terrain/OgreTerrain.h"
#include "Terrain/OgreTerrainGroup.h"

#define TERRAIN_WORLD_SIZE 12000.0f
#define TERRAIN_SIZE 513

using namespace Ogre;

AnimationState *as;

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    MyTestApp();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    void initBlendMaps(Terrain *terrain);
};

//! [constructor]
MyTestApp::MyTestApp() : OgreBites::ApplicationContext("OgreTutorialApp")
{
}
//! [constructor]

SceneNode* node;

SceneNode* camNode;

TerrainGroup *terrainGroup;

//! [key_handler]
bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    /*if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    } else if (evt.keysym.sym == OgreBites::SDLK_LEFT) {
        node->rotate(Ogre::Quaternion(Ogre::Degree(-2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
    } else if (evt.keysym.sym == OgreBites::SDLK_RIGHT) {
        node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
    }*/
    SceneNode *node = camNode;
    Real moveDistance = 10;
    switch (evt.keysym.sym) {
        case OgreBites::SDLK_ESCAPE:
            getRoot()->queueEndRendering();
            break;
        case OgreBites::SDLK_LEFT:
            node->setPosition(Vector3(node->getPosition().x - moveDistance, node->getPosition().y, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(-2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_RIGHT:
            node->setPosition(Vector3(node->getPosition().x + moveDistance, node->getPosition().y, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_DOWN:
            node->setPosition(Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z - moveDistance));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_UP:
            node->setPosition(Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z + moveDistance));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::SDLK_SPACE:
            node->setPosition(Vector3(node->getPosition().x, node->getPosition().y + moveDistance, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        case OgreBites::KMOD_CTRL:
            node->setPosition(Vector3(node->getPosition().x, node->getPosition().y - moveDistance, node->getPosition().z));
//            node->rotate(Ogre::Quaternion(Ogre::Degree(2),Ogre::Vector3(0,0,1)), Ogre::Node::TS_LOCAL);
            break;
        default:
            break;
    }
    Vector3 pos = node->getPosition();
//    printf("position: %f, %f, %f\n", pos.x, pos.y, pos.z);
    return true;
}
//! [key_handler]

bool isTerrainsImported = false;

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
    light->setType(Light::LT_SPOTLIGHT);
    light->setDiffuseColour(ColourValue::White);
    light->setSpecularColour(ColourValue(0.4, 0.4, 0.4));
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 3000, 0);
    lightNode->attachObject(light);

    // also need to tell where we are
    camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 1500, 0);
    camNode->lookAt(Vector3(0, 0, -1000), Node::TS_WORLD);

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(0.1); // specific to this sample
//    cam->setFarClipDistance(0); // specific to this sample
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

    // terrain
    // terrain global options
    TerrainGlobalOptions *terrainGlobal = new TerrainGlobalOptions();

    // terrain group
    terrainGroup = OGRE_NEW TerrainGroup(scnMgr, Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
    terrainGroup->setFilenameConvention("temp", "ter");
    terrainGroup->setOrigin(Vector3(0, 0, 0));

    // terrain defaults global
    terrainGlobal->setMaxPixelError(8);
    terrainGlobal->setCompositeMapDistance(3000);
    terrainGlobal->getDefaultMaterialGenerator()->setLightmapEnabled(false);
    terrainGlobal->setLightMapDirection(light->getDerivedDirection());
    terrainGlobal->setCompositeMapAmbient(scnMgr->getAmbientLight());
    terrainGlobal->setCompositeMapDiffuse(light->getDiffuseColour());

    // terrain defaults
    Terrain::ImportData& defaultimp = terrainGroup->getDefaultImportSettings();
    defaultimp.inputScale = 600;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
    defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 200;
    defaultimp.layerList[0].textureNames.push_back("Ground37_diffspec.dds");
    defaultimp.layerList[0].textureNames.push_back("Ground37_normheight.dds");
    defaultimp.layerList[1].worldSize = 200;
    defaultimp.layerList[1].textureNames.push_back("Ground23_diffspec"); // loaded from memory
    defaultimp.layerList[1].textureNames.push_back("Ground23_normheight.dds");
    defaultimp.layerList[2].worldSize = 400;
    defaultimp.layerList[2].textureNames.push_back("Rock20_diffspec.dds");
    defaultimp.layerList[2].textureNames.push_back("Rock20_normheight.dds");

    // generate terrains
    long TERRAIN_PAGE_MIN_X = -0, TERRAIN_PAGE_MAX_X = 0;
    long TERRAIN_PAGE_MIN_Y = -0, TERRAIN_PAGE_MAX_Y = 0;
    for (long x = TERRAIN_PAGE_MIN_X; x <= TERRAIN_PAGE_MAX_X; ++x) {
        for (long y = TERRAIN_PAGE_MIN_Y; y <= TERRAIN_PAGE_MAX_Y; ++y) {
            String filename = terrainGroup->generateFilename(x, y);
            printf("%s\n", filename.c_str());
            if (ResourceGroupManager::getSingleton().resourceExists(terrainGroup->getResourceGroup(), filename)) {
                terrainGroup->defineTerrain(x, y);
            } else {
                Image img;
                img.load("terrain.png", terrainGroup->getResourceGroup());
                terrainGroup->defineTerrain(x, y, &img);
                isTerrainsImported = true;
            }
        }
    }
    // sync load since we want everything in place when we start
    terrainGroup->loadAllTerrains(true);

    if (isTerrainsImported) {
        printf("seeee\n");
        for (const auto& ti : terrainGroup->getTerrainSlots()) {
            initBlendMaps(ti.second->instance);
        }
    }
    terrainGroup->freeTemporaryResources();
}
//! [setup]

void MyTestApp::initBlendMaps(Terrain *terrain) {
    TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    float minHeight0 = 20;
    float fadeDist0 = 15;
    float minHeight1 = 70;
    float fadeDist1 = 15;
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
    for (uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Real tx, ty;

            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            float height = terrain->getHeightAtTerrainPosition(tx, ty);

            *pBlend0++ = Math::saturate((height - minHeight0) / fadeDist0);
            *pBlend1++ = Math::saturate((height - minHeight1) / fadeDist1);
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}

//TrayManager
//mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "", 350);

//! [loop]
bool MyTestApp::frameRenderingQueued(const Ogre::FrameEvent& evt) {
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
//! [loop]

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
