//
// Created by durda on 2/14/21.
//

#ifndef PROJECT2_BULLET_H
#define PROJECT2_BULLET_H

#include "MovingObject.h"

//#include "Boom.h"

class Bullet : public MovingObject
{
private:
    bool power;
    Boom* boom;
public:
    Bullet(int xpos, int ypos);
//    ~Bullet() override;
    Boom* getBoom() { return boom; }
    bool& isPower() { return power; }
    void handleObjectNearBorder() override;
    void handleThisObjectIfEncounteredWithAnother(Object* anotherObject, Boom* boomchik) override;
    void bulletAppears(int xTankPos, int yTankPos, int tankWidth, int tankHeight, ObjectDirection dir);
    void move() override;
    void draw() override;
};


#endif //PROJECT2_BULLET_H
