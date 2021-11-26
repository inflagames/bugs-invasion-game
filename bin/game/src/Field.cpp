//
// Created by guille on 13.11.21.
//

#include <set>
#include <map>
#include <cmath>
#include "../inc/Field.h"
#include "../inc/Utils.h"

void Field::createField(SceneManager *scnMgrIns, Light *light) {
    this->scnMgr = scnMgrIns;

    terrainEntity = scnMgrIns->createEntity("terrain", "terrain.mesh");
    terrainNode = scnMgrIns->getRootSceneNode()->createChildSceneNode();
    terrainNode->attachObject(terrainEntity);
    terrainNode->setPosition(0, 0, 0);
}

void Field::createPhysicEntity(Physics *physics) {


/*    size_t vertex_count, index_count;
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
    std::map<std::pair<Real, Real>, Real> points;
    float minHeight = vertices[0].y;
    float maxHeight = vertices[0].y;
    for (int i = 0; i < vertex_count; i++) {
        Ogre::Vector3 p = vertices[i];
        xPoints.insert(p.x);
        zPoints.insert(p.z);
        points[{p.x, p.z}] = p.y;
        minHeight = std::min(minHeight, p.y);
        maxHeight = std::max(maxHeight, p.y);
//        printf("X: %lf, Z: %lf, Y: %lf\n", p.x, p.z, p.y);
    }
//    maxHeight = std::max(std::abs(minHeight), std::abs(maxHeight));
//    minHeight = -maxHeight;
//    printf("XGrid: %ld\n", xPoints.size());
//    printf("ZGrid: %ld\n", zPoints.size());

    const int nbRows = int(xPoints.size());
    const int nbColumns = int(zPoints.size());

    auto it = xPoints.begin();
    for (int i = 0; it != xPoints.end(); i++, it++) {
        auto itz = zPoints.begin();
        for (int j = 0; itz != zPoints.end(); j++, itz++) {
            heightValues[i * nbColumns + j] = points[{(*it), -(*itz)}];
        }
    }

    // Create the heightfield collision shape
    HeightFieldShape *heightFieldShape = physicsCommon->createHeightFieldShape(nbColumns,
                                                                               nbRows, minHeight,
                                                                               maxHeight, heightValues,
                                                                               HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
    *//*
     x = X * s
     x / X = s
     *//*
    reactphysics3d::Vector3 v1;
    reactphysics3d::Vector3 v2;
    heightFieldShape->getLocalBounds(v1, v2);
    Real scaleFactor = std::abs(*xPoints.begin()) / v2.x;
    heightFieldShape->setScale(reactphysics3d::Vector3(scaleFactor, 1, scaleFactor));
    heightFieldShape->getLocalBounds(v1, v2);

    Real heightOffset = minHeight - v1.y;
    rp3d::Vector3 position = Utils::toRp3Vector3(terrainNode->getPosition());
    reactphysics3d::Transform transform(
            rp3d::Vector3(position.x, position.y + heightOffset, position.z),
            reactphysics3d::Quaternion::identity());
    fieldBody = world->createRigidBody(transform);
    fieldBody->setType(reactphysics3d::BodyType::STATIC);
    fieldBody->addCollider(heightFieldShape, Transform::identity());*/
}

void Field::render(const FrameEvent &evt) {
    // todo
}
