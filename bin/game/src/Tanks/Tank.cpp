//
// Created by guille on 13.11.21.
//

#include "../../inc/Tanks/Tank.h"

Tank::Tank(SceneManager *scnMgr) {
    tankEntity = scnMgr->createEntity("tank.mesh");
    tankNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    tankNode->attachObject(tankEntity);
    tankNode->setPosition(0, 35, 0);

//    AnimationStateSet *some = tankEntity->getAllAnimationStates();
//    if (some != nullptr) {
//        printf("-----ANIMATIONS-----\n");
//        AnimationStateIterator asi = some->getAnimationStateIterator();
//        int c = 0;
//        while (asi.hasMoreElements()) {
//            printf("%s\n", asi.current()->first.c_str());
//            asi.moveNext();
//            c++;
//        }
//        printf("%d\n", c);
//    }

//    tankAnimationEntity = tankEntity->getAnimationState("rotate_cannon");
//    tankAnimationEntity->setWeight(2);
//    tankAnimationEntity->setTimePosition(0);
//    tankAnimationEntity->setLoop(true);
//    tankAnimationEntity->setEnabled(true);
}

void Tank::rotateCannon(Real angle) {

}

void Tank::render(const FrameEvent &evt) {
//    Real time = evt.timeSinceLastFrame;
//    tankAnimationEntity->addTime(time);

//    btTransform pos;
//    tankBody->getMotionState()->getWorldTransform(pos);

//    printf("x: %f, y: %f, z: %f\n", pos.x, pos.y, pos.z);
//    tankNode->setPosition(pos.getOrigin().x(), pos.getOrigin().y(), pos.getOrigin().z());
//    tankNode->setOrientation(Utils::toOgreQuaternion(pos.getRotation()));

//    Ogre::Vector3 tankPosition = tankNode->getPosition();
//    camNode->setPosition(tankPosition.x, tankPosition.y + 20, tankPosition.z + 30);
//    camNode->lookAt(tankNode->getPosition(), Ogre::Node::TS_WORLD);
}

void Tank::createPhysicEntity(Physics *physics) {
//    dynamicsWorld = dynamicsWorldIns;

//    Ogre::Vector3 tankPosition = tankNode->getPosition();

//    auto *tankShape =
//            new btBoxShape(btVector3(btScalar(2.26), btScalar(0.82), btScalar(4.59)));
//    btTransform transform;
//    transform.setIdentity();
//    transform.setOrigin(btVector3(btScalar(tankPosition.x), btScalar(tankPosition.y), btScalar(tankPosition.z)));
//    transform.setOrigin(btVector3(0,0,0));

//    auto *motionState = new btDefaultMotionState(transform);
//    auto *motionState = new btDefaultMotionState(btTransform::getIdentity());
//    btRigidBody::btRigidBodyConstructionInfo tankInfo(btScalar(10),
//                                                      motionState,
//                                                      tankShape,
//                                                      btVector3(btScalar(0), btScalar(0), btScalar(0)));
//    auto *tankBody = new btRigidBody(tankInfo);
//    tankBody->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);

//    physics->getDynamicsWorld()->addRigidBody(tankBody);
}

Real const FORCE = 200;

void Tank::moveForward() {
//    Real force = FORCE;
//    rp3d::Quaternion ori = tankPhysicBody->getTransform().getOrientation();
//    rp3d::Vector3 forceVector(0, 0, force);
//    forceVector = ori * forceVector;
}

void Tank::moveBack() {
//    Real force = FORCE;
//    rp3d::Quaternion ori = tankPhysicBody->getTransform().getOrientation();
//    rp3d::Vector3 forceVector(0, 0, -force);
//    forceVector = ori * forceVector;
}

void Tank::moveLeft() {
//    Real force = 50;
//    rp3d::Quaternion ori = tankPhysicBody->getTransform().getOrientation();
//    rp3d::Vector3 forceVector(0, force, 0);
//    forceVector = ori * forceVector;
}

void Tank::moveRight() {
//    Real force = 50;
//    rp3d::Quaternion ori = tankPhysicBody->getTransform().getOrientation();
//    rp3d::Vector3 forceVector(0, -force, 0);
//    forceVector = ori * forceVector;
}
