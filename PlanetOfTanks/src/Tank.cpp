//
// Created by durda on 2/14/21.
//

#include "Tank.h"
#include "GameMap.h"

Tank::Tank(int xpos, int ypos)  : MovingObject(xpos, ypos), health(1), countOfBullets(1), level(0), keyPressed(false)
{
    for (int i = 0; i < countOfBullets; ++i)
        bullets.push_back(new Bullet(xpos, ypos));

    startedAnimation = new StartedAnimation(xpos, ypos);
}

//Tank::~Tank() {
//    for (auto sprite : objectDirection)
//        destroySprite(sprite);
//
//    delete startedAnimation;
//}

void Tank::setBulletActive(const bool &shot)
{
    for (Bullet* bullet : bullets)
    {
        if (!bullet->isActive())
        {
            bullet->isActive() = shot;
            bullet->bulletAppears(x, y, width, height, activeDirection);
            break;
        }
    }
}

void Tank::handleObjectNearBorder()
{
    if (x > GAMEMAP_WIDTH - width)
        x = GAMEMAP_WIDTH - width;
    else if (x < 0)
        x = 0;
    else if (y > GAMEMAP_HEIGHT - height)
        y = GAMEMAP_HEIGHT - height;
    else if (y < 0)
        y = 0;
}

void Tank::handleThisObjectIfEncounteredWithAnother(Object* anotherObject, Boom* boomchik)
{
    int xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj;
    anotherObject->getParameters(xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj);

    if (activeDirection == RIGHT && x + width > xAnotherObj && x < xAnotherObj)
        x = xAnotherObj - width;
    else if (activeDirection == LEFT && x < xAnotherObj + widthAnotherObj && xAnotherObj < x)
        x = xAnotherObj + widthAnotherObj;
    else if (activeDirection == DOWN && y + height > yAnotherObj && y < yAnotherObj)
        y = yAnotherObj - height;
    else if (activeDirection == UP && y < yAnotherObj + heightAnotherObj && yAnotherObj < y)
        y = yAnotherObj + heightAnotherObj;
}

void Tank::move()
{
    switch (activeDirection)
    {
        case RIGHT:
        case LEFT:
            getSpriteSize(objectDirection[0 + 4*level], width, height);
            break;
        case DOWN:
        case UP:
            getSpriteSize(objectDirection[2 + 4*level], width, height);
            break;
    }
    MovingObject::move();
}

void Tank::draw()
{
    if (startedAnimation->isActive())
    {
        startedAnimation->draw();
        for (Bullet* bullet : bullets )
            bullet->isActive() = false;
    }
    else
        switch (activeDirection)
        {
            case RIGHT:
                drawSprite(objectDirection[0+level*4], x, y);
                break;
            case LEFT:
                drawSprite(objectDirection[1+level*4], x, y);
                break;
            case DOWN:
                drawSprite(objectDirection[2+level*4], x, y);
                break;
            case UP:
                drawSprite(objectDirection[3+level*4], x, y);
                break;
        }
}

void Tank::getParameters(int &xpos, int &ypos, int &objWidth, int &objHeight, ObjectDirection &objDir)
{
    switch (activeDirection)
    {
        case RIGHT:
        case LEFT:
            getSpriteSize(objectDirection[0 + 4*level], width, height);
            break;
        case DOWN:
        case UP:
            getSpriteSize(objectDirection[2 + 4*level], width, height);
            break;
    }
    xpos = x; ypos = y; objWidth = width; objHeight = height; objDir = activeDirection;
}

MyTank::MyTank(int xpos, int ypos) : Tank(xpos, ypos), counterOfSimultaneouslyPressedKeys(0)
{
    for (int levelVal = 0; levelVal < 4; ++levelVal)
    {
        std::string path;
        path = "../images/Player1_Level" + std::to_string(levelVal) + "_Right.png";
        objectDirection.push_back(createSprite(path.c_str()));
        path = "../images/Player1_Level" + std::to_string(levelVal) + "_Left.png";
        objectDirection.push_back(createSprite(path.c_str()));
        path = "../images/Player1_Level" + std::to_string(levelVal) + "_Down.png";
        objectDirection.push_back(createSprite(path.c_str()));
        path = "../images/Player1_Level" + std::to_string(levelVal) + "_Up.png";
        objectDirection.push_back(createSprite(path.c_str()));
    }

    getSpriteSize(objectDirection[0], width, height);
    active = true;
}

void MyTank::pressKey(bool press)
{
    if (press)
        counterOfSimultaneouslyPressedKeys++;
    else
        counterOfSimultaneouslyPressedKeys--;
    keyPressed = counterOfSimultaneouslyPressedKeys;
}


void MyTank::move()
{
//        So, the tank moves when bool tankMoves==true or there couple of keys pressed.
    if ((keyPressed || counterOfSimultaneouslyPressedKeys) && !startedAnimation->isActive() && active)
        Tank::move();
}

void MyTank::draw()
{
    if (active)
        Tank::draw();
}

EnemyTank::EnemyTank(int xpos, int ypos) : Tank(xpos, ypos)
{
    active = true;
    objectDirection.push_back(createSprite("../images/Enemy1_Right.png"));
    objectDirection.push_back(createSprite("../images/Enemy1_Left.png"));
    objectDirection.push_back(createSprite("../images/Enemy1_Down.png"));
    objectDirection.push_back(createSprite("../images/Enemy1_Up.png"));

    getSpriteSize(objectDirection[0], width, height);
}

void EnemyTank::move() {
    if (active)
    {
        if (lastFrame%(rand()%1000+300) == 300 && !startedAnimation->isActive())
            setBulletActive(true);

        if (lastFrame%(rand()%1000+500) == 500)
            activeDirection = static_cast<ObjectDirection>(rand()%4);

        if (lastFrame%(rand()%1000+500) == 500)
            keyPressed = true;
        else if (lastFrame%(rand()%1000+500) == 1500)
            keyPressed = false;

        if (keyPressed && !startedAnimation->isActive())
            Tank::move();
    }
}

void EnemyTank::draw() {
    if (active)
        Tank::draw();
}
