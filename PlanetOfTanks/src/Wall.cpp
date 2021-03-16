//
// Created by durda on 2/14/21.
//

#include "Wall.h"

void Wall::draw()
{
    drawSprite(object, x, y);
}

BrickWall::BrickWall(int xpos, int ypos) : Wall(xpos, ypos)
{
    breakable = true;
    object = createSprite("../images/Brick_Wall.png");
    getSpriteSize(object, width, height);
}

void BrickWall::draw() { Wall::draw(); }

SteelWall::SteelWall(int xpos, int ypos) : Wall(xpos, ypos)
{
    breakable = false;
    object = createSprite("../images/Steel_Wall.png");
    getSpriteSize(object, width, height);
}

void SteelWall::draw() { Wall::draw(); }