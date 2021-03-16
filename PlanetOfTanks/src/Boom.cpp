//
// Created by durda on 2/14/21.
//

#include "Boom.h"

Boom::Boom(int xpos, int ypos) : AnimatedObject(xpos, ypos)
{
    images.push_back(createSprite("../images/Boom_0.png"));
    images.push_back(createSprite("../images/Boom_1.png"));
    images.push_back(createSprite("../images/Boom_2.png"));
}

//Boom::~Boom()
//{
//
//}


void Boom::boomAppears(int xObjectPos, int yObjectPos, int objectWidth, int objectHeight, ObjectDirection dir)
{
    switch (dir)
    {
        case RIGHT:
            x = xObjectPos + objectWidth - width/2;
            y = yObjectPos + objectHeight/2 - height/2;
            break;
        case LEFT:
            x = xObjectPos - width/2;
            y = yObjectPos + objectHeight/2 - height/2;
            break;
        case DOWN:
            x = xObjectPos + objectWidth/2 - width/2;
            y = yObjectPos + objectHeight - height/2;
            break;
        case UP:
            x = xObjectPos + objectWidth/2 - width/2;
            y = yObjectPos - height/2;
            break;
    }
}

void Boom::draw()
{
    frequency = (lastFrame - startTiming) % duration;
    if (frequency < duration * 1 / 6)
        drawSprite(images[0], x, y);
    else if (frequency < duration * 2 / 6)
        drawSprite(images[1], x, y);
    else if (frequency < duration * 3 / 6)
        drawSprite(images[2], x, y);
}

SmallBoom::SmallBoom(int xpos, int ypos) : Boom(xpos, ypos)
{
    getSpriteSize(images.back(), width, height);
}

void SmallBoom::draw()
{
    if (active)
    {
        Boom::draw();
        if (frequency > duration * 3 / 6)
            active = false;
    }
}


BigBoom::BigBoom(int xpos, int ypos) : Boom(xpos, ypos)
{
    images.push_back(createSprite("../images/Boom_3.png"));
    images.push_back(createSprite("../images/Boom_4.png"));
    getSpriteSize(images.back(), width, height);
}

void BigBoom::boomAppears(int xObjectPos, int yObjectPos, int objectWidth, int objectHeight, ObjectDirection dir)
{
    x = xObjectPos + objectWidth/2 - width/2;
    y = yObjectPos + objectHeight/2 - height/2;
}

void BigBoom::draw()
{
    if (active)
    {
        Boom::draw();
        if (frequency > duration * 3 / 6 && frequency < duration * 4 / 6)
            drawSprite(images[3], x, y);
        else if (frequency > duration * 3 / 6 && frequency < duration * 5 / 6)
            drawSprite(images[4], x, y);
        else if (frequency > duration * 5 / 6)
            active = false;
    }
}

