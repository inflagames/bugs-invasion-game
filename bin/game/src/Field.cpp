//
// Created by guille on 13.11.21.
//

#include "../inc/Field.h"

void Field::createField(SceneManager *scnMgr, Light *light) {
    setupGlobalOptions(scnMgr, light);
    createTerrainGroup(scnMgr);
    loadDefaultTextures();

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
        for (const auto &ti: terrainGroup->getTerrainSlots()) {
            initBlendMaps(ti.second->instance);
        }
    }
    terrainGroup->freeTemporaryResources();
}

void Field::setupGlobalOptions(SceneManager *scnMgr, Light *light) {
    terrainGlobal = new TerrainGlobalOptions();
    terrainGlobal->setMaxPixelError(8);
    terrainGlobal->setCompositeMapDistance(3000);
    terrainGlobal->getDefaultMaterialGenerator()->setLightmapEnabled(false);
    terrainGlobal->setLightMapDirection(light->getDerivedDirection());
    terrainGlobal->setCompositeMapAmbient(scnMgr->getAmbientLight());
    terrainGlobal->setCompositeMapDiffuse(light->getDiffuseColour());
}

void Field::createTerrainGroup(SceneManager *scnMgr) {
    terrainGroup = OGRE_NEW TerrainGroup(scnMgr, Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
    terrainGroup->setFilenameConvention("temp", "ter");
    terrainGroup->setOrigin(Vector3(0, 0, 0));
}

void Field::loadDefaultTextures() {
    Terrain::ImportData &defaultImp = terrainGroup->getDefaultImportSettings();
    defaultImp.inputScale = 600;
    defaultImp.minBatchSize = 33;
    defaultImp.maxBatchSize = 65;
    defaultImp.layerList.resize(3);
    defaultImp.layerList[0].worldSize = 200;
    defaultImp.layerList[0].textureNames.push_back("Ground37_diffspec.dds");
    defaultImp.layerList[0].textureNames.push_back("Ground37_normheight.dds");
    defaultImp.layerList[1].worldSize = 200;
    defaultImp.layerList[1].textureNames.push_back("Ground23_diffspec"); // loaded from memory
    defaultImp.layerList[1].textureNames.push_back("Ground23_normheight.dds");
    defaultImp.layerList[2].worldSize = 400;
    defaultImp.layerList[2].textureNames.push_back("Rock20_diffspec.dds");
    defaultImp.layerList[2].textureNames.push_back("Rock20_normheight.dds");
}

void Field::initBlendMaps(Terrain *terrain) {
    TerrainLayerBlendMap *blendMap0 = terrain->getLayerBlendMap(1);
    TerrainLayerBlendMap *blendMap1 = terrain->getLayerBlendMap(2);
    float minHeight0 = 20;
    float fadeDist0 = 15;
    float minHeight1 = 70;
    float fadeDist1 = 15;
    float *pBlend0 = blendMap0->getBlendPointer();
    float *pBlend1 = blendMap1->getBlendPointer();
    for (uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y) {
        for (uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x) {
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
