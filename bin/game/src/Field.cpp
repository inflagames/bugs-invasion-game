//
// Created by guille on 13.11.21.
//

#include <set>
#include "../inc/Field.h"
#include "../inc/Utils.h"

void Field::createField(SceneManager *scnMgr, Light *light) {
    this->scnMgr = scnMgr;

    terrainEntity = scnMgr->createEntity("terrain", "terrain.mesh");
    terrainNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    terrainNode->attachObject(terrainEntity);
    terrainNode->setPosition(0, 0, 0);
}

void Field::createPhysicEntity(PhysicsWorld *world, PhysicsCommon *physicsCommon) {
    size_t vertex_count, index_count;
    Ogre::Vector3 *vertices;
    unsigned long *indices;

    Utils::getMeshInformation(terrainEntity->getMesh().get(),
                              vertex_count,
                              vertices,
                              index_count,
                              indices,
                              terrainNode->getPosition(),
                              terrainNode->getOrientation(),
                              terrainNode->getScale());

    std::set<Real> xPoints;
    std::set<Real> zPoints;
    for (int i = 0; i < vertex_count; i++) {
        Ogre::Vector3 p = vertices[i];
        xPoints.insert(p.x);
        zPoints.insert(p.z);
        printf("X: %f\n", p.x);
    }
    printf("XGrid: %ld\n", xPoints.size());
    printf("ZGrid: %ld\n", zPoints.size());

    const int nbRows = 2;//int(xPoints.size());
    const int nbColumns = 2;//int(zPoints.size());
    float minHeight = 0;
    float maxHeight = 0;

    for (int i = 0; i < nbRows; i++) {
        for (int j = 0; j < nbColumns; j++) {
            heightValues[i * nbColumns + j] = 0;
        }
    }

    // Create the heightfield collision shape
    HeightFieldShape *heightFieldShape = physicsCommon->createHeightFieldShape(nbColumns,
                                                                               nbRows, minHeight,
                                                                               maxHeight, heightValues,
                                                                               HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
    reactphysics3d::Vector3 v1;
    reactphysics3d::Vector3 v2;
    heightFieldShape->setScale(reactphysics3d::Vector3(1000, 1, 1000));
    heightFieldShape->getLocalBounds(v1, v2);

    reactphysics3d::Transform transform(
            Utils::toRp3Vector3(terrainNode->getPosition()),
            reactphysics3d::Quaternion::identity());
    fieldBody = world->createRigidBody(transform);
    fieldBody->setType(reactphysics3d::BodyType::STATIC);
    fieldBody->addCollider(heightFieldShape, Transform::identity());
}

void Field::render(const FrameEvent &evt) {
    // todo
}
