//
// Created by durda on 2/17/21.
//

#ifndef PLANETOFTANKS_BONUS_H
#define PLANETOFTANKS_BONUS_H

#include "AnimatedObject.h"

class Bonus : public AnimatedObject
{
protected:
public:
    Bonus(int xpos, int ypos) : AnimatedObject(xpos, ypos)
    { duration = 10000; startTiming = lastFrame; frequency = 400; }

    void draw() override
    {
        if (active && lastFrame < duration + startTiming)
        {
            if (lastFrame%frequency < frequency/2)
                drawSprite(images.front(), x, y);
        }
        else
            active = false;
    }
};

class BonusTank : public Bonus
{
private:
public:
    BonusTank(int xpos, int ypos) : Bonus(xpos, ypos)
    {
        images.push_back(createSprite("../images/Bonus_Tank.png"));
        getSpriteSize(images.front(), width, height);
    }
};

class BonusStar : public Bonus
{
private:
public:
    BonusStar(int xpos, int ypos) : Bonus(xpos, ypos)
    {
        images.push_back(createSprite("../images/Bonus_Star.png"));
        getSpriteSize(images.front(), width, height);
    }
};


#endif //PLANETOFTANKS_BONUS_H
