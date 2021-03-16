//
// Created by durda on 2/15/21.
//

#ifndef PROJECT2_MOVINGOBJECT_H
#define PROJECT2_MOVINGOBJECT_H

#include "Object.h"
#include "Boom.h"
//#include "GameMap.h"

class MovingObject : public Object
{
protected:
    int movementSpeed;
    std::vector<Sprite*> objectDirection;
    ObjectDirection activeDirection;
public:
    MovingObject(int xpos, int ypos);
//    ~MovingObject() override;

    virtual void setMovementSpeed(int speed) { movementSpeed = speed; }
    virtual void getParameters (int &xpos, int &ypos, int &objWidth, int &objHeight, ObjectDirection &dir)
    { xpos = x; ypos = y; objWidth = width; objHeight = height; dir = activeDirection; }
    virtual void handleObjectNearBorder() = 0;
    virtual void handleThisObjectIfEncounteredWithAnother(Object* anotherObject, Boom* boomchik) = 0;
    virtual void move() = 0;
    void draw() override = 0;
};


#endif //PROJECT2_MOVINGOBJECT_H
