//
// Created by durda on 2/14/21.
//

#ifndef PROJECT2_BOOM_H
#define PROJECT2_BOOM_H

#include "AnimatedObject.h"
//#include "MovingObject.h"

class Boom : public AnimatedObject
{
public:
    Boom(int xpos, int ypos);
//    ~Boom() override;
    virtual void boomAppears(int xObjectPos, int yObjectPos, int objectWidth, int objectHeight, ObjectDirection dir);
    void draw() override = 0;
};

class SmallBoom : public Boom
{
public:
    SmallBoom(int xpos, int ypos);

    void draw() override;
};

class BigBoom : public Boom
{
public:
    BigBoom(int xpos, int ypos);
    void boomAppears(int xObjectPos, int yObjectPos, int objectWidth, int objectHeight, ObjectDirection dir) override;
    void draw() override;
};


#endif //PROJECT2_BOOM_H
