//
// Created by durda on 2/14/21.
//

#include "Bullet.h"
#include "Tank.h"
#include "GameMap.h"


Bullet::Bullet(int xpos, int ypos) : MovingObject(xpos, ypos), power(false)
{
//    active = false;
    movementSpeed = 3;
    objectDirection.push_back(createSprite("../images/Bullet_Right.png"));
    objectDirection.push_back(createSprite("../images/Bullet_Left.png"));
    objectDirection.push_back(createSprite("../images/Bullet_Down.png"));
    objectDirection.push_back(createSprite("../images/Bullet_Up.png"));

    boom = new SmallBoom(xpos, ypos);
}

//Bullet::~Bullet()
//{
//    for (auto sprite : objectDirection)
//        destroySprite(sprite);
//
//    delete boom;
//}


void Bullet::handleObjectNearBorder()
{
    if ((x > GAMEMAP_WIDTH - width   || x < 0 ||
        y > GAMEMAP_HEIGHT - height || y < 0) && active)
        handleThisObjectIfEncounteredWithAnother(this, new SmallBoom(0, 0));
}


void Bullet::handleThisObjectIfEncounteredWithAnother(Object* anotherObject, Boom* boomchik)
{
    int xAnotherObj = x, yAnotherObj = y, widthAnotherObj = width, heightAnotherObj = height;
    if (dynamic_cast<Tank*>(anotherObject))
        anotherObject->getParameters(xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj);


    if (!getBoom()->isActive() && isActive())
    {
        boom = boomchik;
        active = false;
        boom->isActive() = true;
        boom->resetTiming();
        boom->boomAppears(xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj, activeDirection);
    }
}


void Bullet::bulletAppears(int xTankPos, int yTankPos, int tankWidth, int tankHeight, ObjectDirection dir)
{
    activeDirection = dir;
    getSpriteSize(objectDirection[dir], width, height);
    switch (activeDirection)
    {
        case RIGHT:
            x = xTankPos + tankWidth - 10;
            y = yTankPos + (tankHeight>>1) - (height>>1);
            break;
        case LEFT:
            x = xTankPos - width + 10;
            y = yTankPos + (tankHeight>>1) - (height>>1);
            break;
        case DOWN:
            x = xTankPos + (tankWidth>>1) - (width>>1);
            y = yTankPos + tankHeight - 10;
            break;
        case UP:
            x = xTankPos + (tankWidth>>1) - (width>>1);
            y = yTankPos - height + 10;
            break;
    }
}

void Bullet::move()
{
    if (active)
        MovingObject::move();
    else
        x = SCREEN_WIDTH;
}

void Bullet::draw()
{
    if (active)
        MovingObject::draw();
}
