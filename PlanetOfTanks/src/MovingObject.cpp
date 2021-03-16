//
// Created by durda on 2/15/21.
//

#include "MovingObject.h"

MovingObject::MovingObject(int xpos, int ypos) : Object(xpos, ypos), activeDirection(UP), movementSpeed(1){ }

//MovingObject::~MovingObject()
//{
//    for (auto sprite : objectDirection)
//        destroySprite(sprite);
//}

void MovingObject::move() {

    {
//        Since our positions and ticks have an integer type, I can't reduce the speed of the object by
//        multiplying it by 0.1 or something. So here I went for a trick and change position every 6 ticks.
        if (accurateTickCount % 6 == 0)
            switch (activeDirection)
            {
                case RIGHT:
                    x += static_cast<int>(deltaTime) * movementSpeed;
                    break;
                case LEFT:
                    x -= static_cast<int>(deltaTime) * movementSpeed;
                    break;
                case DOWN:
                    y += static_cast<int>(deltaTime) * movementSpeed;
                    break;
                case UP:
                    y -= static_cast<int>(deltaTime) * movementSpeed;
            }
    }
}

void MovingObject::draw()
{
    switch (activeDirection)
    {
        case RIGHT:
            drawSprite(objectDirection[0], x, y);
            break;
        case LEFT:
            drawSprite(objectDirection[1], x, y);
            break;
        case DOWN:
            drawSprite(objectDirection[2], x, y);
            break;
        case UP:
            drawSprite(objectDirection[3], x, y);
            break;
    }
}


