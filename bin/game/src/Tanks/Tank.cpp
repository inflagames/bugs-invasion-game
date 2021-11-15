//
// Created by guille on 13.11.21.
//

#include "../../inc/Tanks/Tank.h"

Tank::Tank(SceneManager *scnMgr, SceneNode *camNode) {
    this->camNode = camNode;

    tankEntity = scnMgr->createEntity("tank.mesh");
    tankNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    tankNode->attachObject(tankEntity);
    tankNode->setPosition(0, 40, 0);

    AnimationStateSet *some = tankEntity->getAllAnimationStates();
    if (some != nullptr) {
        printf("-----ANIMATIONS-----\n");
        AnimationStateIterator asi = some->getAnimationStateIterator();
        int c = 0;
        while (asi.hasMoreElements()) {
            printf("%s\n", asi.current()->first.c_str());
            asi.moveNext();
            c++;
        }
        printf("%d\n", c);
    }

    tankAnimationEntity = tankEntity->getAnimationState("rotate_cannon");
    tankAnimationEntity->setWeight(1);
    tankAnimationEntity->setTimePosition(0);
    tankAnimationEntity->setLoop(true);
    tankAnimationEntity->setEnabled(true);
}

void Tank::rotateCannon(Real angle) {

}

void Tank::render(const FrameEvent &evt) {
//    Real time = evt.timeSinceLastFrame;
//    tankAnimationEntity->addTime(time);

    reactphysics3d::Vector3 pos = tankPhysicBody->getTransform().getPosition();
//    printf("x: %f, y: %f, z: %f\n", pos.x, pos.y, pos.z);
    tankNode->setPosition(pos.x, pos.y, pos.z);
    tankNode->setOrientation(Utils::toOgreQuaternion(tankPhysicBody->getTransform().getOrientation()));

    Ogre::Vector3 tankPosition = tankNode->getPosition();
    camNode->setPosition(tankPosition.x, tankPosition.y + 20, tankPosition.z + 30);
    camNode->lookAt(tankNode->getPosition(), Ogre::Node::TS_WORLD);
}

void Tank::createPhysicEntity(PhysicsWorld *world, PhysicsCommon *physicsCommon) {
    Ogre::Vector3 tankPosition = tankNode->getPosition();
    reactphysics3d::Transform transform(
            reactphysics3d::Vector3(tankPosition.x, tankPosition.y, tankPosition.z),
            reactphysics3d::Quaternion::identity());
    tankPhysicBody = world->createRigidBody(transform);
    tankPhysicBody->setType(reactphysics3d::BodyType::DYNAMIC);
    tankPhysicBody->setMass(30);

    size_t vertex_count, index_count;
    Ogre::Vector3 *vertices;
    unsigned long *indices;

    Utils::getMeshInformation(tankEntity->getMesh().get(),
                              vertex_count,
                              vertices,
                              index_count,
                              indices,
                              tankNode->getPosition(),
                              tankNode->getOrientation(),
                              tankNode->getScale());

    const reactphysics3d::Vector3 halfExtents(2.26, 0.82, 4.59);
    BoxShape *boxShape = physicsCommon->createBoxShape(halfExtents);
    rp3d::Transform colliderTrans(
            rp3d::Vector3(0, -0.82, 0),
            rp3d::Quaternion::identity());
    tankPhysicBody->addCollider(boxShape, colliderTrans);
}
