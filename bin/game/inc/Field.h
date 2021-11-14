//
// Created by guille on 13.11.21.
//

#ifndef BUGSINVATION_FIELD_H
#define BUGSINVATION_FIELD_H

#include "Ogre.h"
#include "Terrain/OgreTerrain.h"
#include "Terrain/OgreTerrainGroup.h"
#include "PhysicBase.h"

using namespace Ogre;

class Field : public PhysicBase {
public:
    void createField(SceneManager *scnMgr, Light *light);

    void initBlendMaps(Terrain *terrain);

    void createPhysicEntity(PhysicsWorld *world, PhysicsCommon *physicsCommon);

private:
    int TERRAIN_SIZE = 513;
    Real TERRAIN_WORLD_SIZE = 12000.0f;

    SceneManager *scnMgr;
    TerrainGlobalOptions *terrainGlobal;
    TerrainGroup *terrainGroup;

    bool isTerrainsImported = false;

    void setupGlobalOptions(SceneManager *scnMgr, Light *light);

    void createTerrainGroup(SceneManager *scnMgr);

    void loadDefaultTextures();

    Ogre::Vector3 getPointHeight(Ogre::Vector3 position);
};

#endif //BUGSINVATION_FIELD_H
