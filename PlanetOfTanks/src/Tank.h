//
// Created by durda on 2/14/21.
//

#ifndef PROJECT2_TANK_H
#define PROJECT2_TANK_H

#include "MovingObject.h"
#include "Bullet.h"
#include "StartedAnimation.h"

//#include "AnimatedObject.h"
//#include "Boom.h"

class Tank : public MovingObject
{
protected:
    int health;
    int level;

    int countOfBullets;

    std::vector<Bullet*> bullets;
    StartedAnimation* startedAnimation;

    bool keyPressed;
public:
    Tank(int xpos, int ypos);
//    ~Tank() override;

    virtual int getHealth() { return health; }
    virtual void damageTank() { --health; }
    virtual void setBulletActive(const bool &shot);
    virtual void setBulletSpeed(int speed)   { for (Bullet* bullet : bullets) bullet->setMovementSpeed(speed);}
    virtual void setPowerBullets(bool power) { for (Bullet* bullet : bullets) bullet->isPower() = power; }
    virtual void setLevel (int lvl) { level = lvl; }
    virtual bool& keyIsPressed() { return keyPressed; }
    StartedAnimation* getStartedAnimation() { return startedAnimation; }
    virtual int getLevel() { return level; }
    void getParameters(int &xpos, int &ypos, int &objWidth, int &objHeight, ObjectDirection& objDir) override;
    void handleObjectNearBorder() override;
    void handleThisObjectIfEncounteredWithAnother(Object* anotherObject, Boom* boomchik) override;

    void move() override = 0;
    void draw() override = 0;
    std::vector<Bullet*>& getBullets() { return bullets; }
};

class MyTank : public Tank
{
private:
//    this parameter is necessary because when 2 keys are pressed simultaneously, the tank won't move
//    (look at the onKeyReleased function in game.cpp)
    int counterOfSimultaneouslyPressedKeys;
public:
    MyTank(int xpos, int ypos);

    void pressKey(bool press);
    void setDirection(ObjectDirection dir) { activeDirection = dir; }
    void increaseHealth() { ++health; };
    void levelUp() { ++level; };
    void move() override;
    void draw() override;
};

class EnemyTank : public Tank
{
public:
    EnemyTank(int xpos, int ypos);
    void move() override;
    void draw() override;
};



#endif //PROJECT2_TANK_H
