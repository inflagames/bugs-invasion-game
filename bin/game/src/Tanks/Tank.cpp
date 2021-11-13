//
// Created by guille on 13.11.21.
//

#include "../../inc/Tanks/Tank.h"

Tank::Tank(SceneManager *scnMgr, SceneNode *camNode) {
    this->camNode = camNode;

    Entity *tankEntity = scnMgr->createEntity("tank.mesh");
    tankNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    tankNode->attachObject(tankEntity);
//    tankNode->rotate(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(1, 0, 0)), Ogre::Node::TS_LOCAL);
//    tankNode->setPosition(Vector3(0, 0, 0));

    AnimationStateSet *some = tankEntity->getAllAnimationStates();
    if (some == nullptr) {
        printf("-----IS NULL-----\n");
    } else {
        printf("-----WITH ANIMATION-----\n");
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
    Real time = evt.timeSinceLastFrame;
    tankAnimationEntity->addTime(time);

    Vector3 tankPosition = tankNode->getPosition();
    camNode->setPosition(tankPosition.x, tankPosition.y + 35, tankPosition.z + 15);
    camNode->lookAt(tankNode->getPosition(), Ogre::Node::TS_WORLD);
}
