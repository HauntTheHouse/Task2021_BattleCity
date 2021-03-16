//
// Created by durda on 2/13/21.
//

#include "GameMap.h"
#include <algorithm>



const int UNIT_SIZE = 25;
const int MAX_LIFE_COUNT = 9;
int enemyTanksLeftToKill = 20;
int myTankLife;

GameMap::GameMap() : active(true)
{
    srand(time(nullptr));
    background = createSprite("../images/Background.png");
    gameOver.push_back(createSprite("../images/Game_Over_1.png"));
    gameOver.push_back(createSprite("../images/Game_Over_2.png"));

    rightInterface = new RightInterface();

    initWalls("../levels/level1.txt");

    phoenix = new Phoenix(12*UNIT_SIZE, 24*UNIT_SIZE);

    addTank(new MyTank(2*4*UNIT_SIZE, 2*12*UNIT_SIZE));
    addBonuses();
}

void GameMap::initWalls(const char *pathToData)
{
    std::ifstream fin(pathToData);
    if(fin.bad())
    {
        std::cerr << "Can't open the file with data of walls position" << std::endl;
        exit(1);
    }

    int xPositionOfWall = 0, yPositionOfWall = 0;
    while(!fin.eof())
    {
        std::string str;
        std::getline(fin, str);
        for (char type : str)
        {
            if (type == EMPTY)
                xPositionOfWall += UNIT_SIZE;
            else if (type == BRICK_WALL)
            {
                walls.push_back(new BrickWall(xPositionOfWall, yPositionOfWall));
                xPositionOfWall += UNIT_SIZE;
            }
            else if (type == STEEL_WALL)
            {
                walls.push_back(new SteelWall(xPositionOfWall, yPositionOfWall));
                xPositionOfWall += UNIT_SIZE;
            }
        }
        xPositionOfWall = 0;
        yPositionOfWall += UNIT_SIZE;
    }
}


void GameMap::addTank(Tank *tank)
{
    movingObjects.push_back(tank);
    for (Bullet* bullet : tank->getBullets())
        movingObjects.push_back(bullet);
}

void GameMap::addBonuses()
{
    bonuses.push_back(new BonusTank(0, 0));
    bonuses.push_back(new BonusStar(0, 0));
}

MyTank* GameMap::getMyTank() const
{
    if(typeid(*movingObjects.front()) == typeid(MyTank))
        return dynamic_cast<MyTank*>(movingObjects.front());
    return nullptr;
}

void GameMap::processObjects()
{
    for (auto movingObjectIter = movingObjects.begin(); movingObjectIter != movingObjects.end(); movingObjectIter++)
    {
        if (*movingObjectIter != nullptr)
        {
            (*movingObjectIter)->move();
            collisionDetection(movingObjectIter);
        }
    }
//    if I delete an element, I set its pointer in movingObjects to nullptr, and here delete this pointers
    movingObjects.erase(std::remove(movingObjects.begin(), movingObjects.end(), nullptr), end(movingObjects));

//    if myTank not destroyed
    if (MyTank* myTank = getMyTank())
    {
//        I check if my tank has been hit by a bullet (myTank not active) and if it has any life
        myTankLife = myTank->getHealth();
        if (!myTank->isActive() && myTankLife) {
//            in that case tank's level progress reset
            myTank->setLevel(0);
            myTank->setPosition(2 * 4 * UNIT_SIZE, 2 * 12 * UNIT_SIZE);
            myTank->isActive() = true;
            myTank->getStartedAnimation()->resetTiming();
            myTank->getStartedAnimation()->isActive() = true;
//            to default 1 tier
            myTank->setBulletSpeed(3);
//            to default 2 tier
            if (myTank->getBullets().size() == 2) {
                *std::next(movingObjects.begin(), 1) = nullptr;
                myTank->getBullets().resize(1);
            }
//            to default 3 tier
            myTank->setPowerBullets(false);
        }
    }
    else
        myTankLife = 0;
    movingObjects.erase(std::remove(movingObjects.begin(), movingObjects.end(), nullptr), end(movingObjects));

//    create enemyTank
    if (lastFrame%3000 == 0 && enemyTanksLeftToKill)
    {
        addTank(new EnemyTank(rand() % (GAMEMAP_WIDTH - 2 * UNIT_SIZE), 0));
        enemyTanksLeftToKill--;
    }

//    create bonus
    if (lastFrame%12000 == 5000)
    {
        int bonus = rand()%2;
        bonuses[bonus]->setPosition(rand()%(GAMEMAP_WIDTH-2*UNIT_SIZE), rand()%(GAMEMAP_WIDTH-2*UNIT_SIZE));
        bonuses[bonus]->resetTiming();
        bonuses[bonus]->isActive() = true;
    }
}

void GameMap::draw()
{
    drawSprite(background, 0, 0);

    rightInterface->draw();

    phoenix->draw();


    for (Wall* wall : walls)
        wall->draw();

    for (Bonus* bonus : bonuses)
        bonus->draw();

    for (auto & movingObject : movingObjects)
    {
        movingObject->draw();

        if (typeid(*movingObject) == typeid(Bullet))
            dynamic_cast<Bullet*>(movingObject)->getBoom()->draw();
    }

    if (!enemyTanksLeftToKill && movingObjects.size() <= 3 && getMyTank())
    {
        drawSprite(gameOver[1], 0, 0);
        active = false;
    }
    else if (typeid(*movingObjects.front()) != typeid(MyTank) || !phoenix->isActive())
    {
        drawSprite(gameOver[0], 0, 0);
        active = false;
    }

}

void GameMap::collisionDetection(std::vector<MovingObject*>::iterator movingObjectIter)
{
    MovingObject *movingObject = *movingObjectIter;
    int xMovObj, yMovObj, widthMovObj, heightMovObj;
    ObjectDirection dirMovObj;
    movingObject->getParameters(xMovObj, yMovObj, widthMovObj, heightMovObj, dirMovObj);

    int xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj;
    ObjectDirection dirAnotherObj;

//        collision detection with screen border
    movingObject->handleObjectNearBorder();

//        collision detection with all walls
    for (auto wallIter = walls.begin(); wallIter != walls.end(); ++wallIter)
    {
        if (*wallIter == nullptr) continue;

        Wall* wall = *wallIter;
        wall->getParameters(xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj);
//            there we limit the number of walls that the movingObject may encounter
        if (xAnotherObj > xMovObj - widthAnotherObj && xAnotherObj < xMovObj + widthMovObj &&
            yAnotherObj > yMovObj - heightAnotherObj && yAnotherObj < yMovObj + heightMovObj)
        {
            movingObject->handleThisObjectIfEncounteredWithAnother(wall, new SmallBoom(0,0));

            if (Bullet *bullet = dynamic_cast<Bullet*>(movingObject))
                if (wall->getBreakable() || bullet->isPower())
                {
                    delete *wallIter;
                    *wallIter = nullptr;
                }
        }
    }
    walls.erase(std::remove(walls.begin(), walls.end(), nullptr), end(walls));

//    collision detection with phoenix
    {
        phoenix->getParameters(xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj);

        if (xAnotherObj > xMovObj - widthAnotherObj && xAnotherObj < xMovObj + widthMovObj &&
            yAnotherObj > yMovObj - heightAnotherObj && yAnotherObj < yMovObj + heightMovObj)
        {
            movingObject->handleThisObjectIfEncounteredWithAnother(phoenix, new BigBoom(xAnotherObj, yAnotherObj));
            if (typeid(*movingObject) == typeid(Bullet))
            {
                phoenix->isActive() = false;
                if (MyTank* myTank = getMyTank())
                    myTank->keyIsPressed() = false;
            }
        }
    }

    for (auto bonusIter = bonuses.begin(); bonusIter != bonuses.end(); ++bonusIter)
    {
        if (typeid(*movingObject) == typeid(MyTank) && (*bonusIter)->isActive())
        {
            Bonus* bonus = (*bonusIter);
            MyTank* myTank = getMyTank();
            int xMyTank, yMyTank, myTankWidth, myTankHeight;
            ObjectDirection myTankDir;
            myTank->getParameters(xMyTank, yMyTank, myTankWidth, myTankHeight, myTankDir);

            int xBonus, yBonus, bonusWidth, bonusHeight;
            bonus->getParameters(xBonus, yBonus, bonusWidth, bonusHeight);

            if (xBonus > xMyTank - bonusWidth  && xBonus < xMyTank + myTankWidth &&
                yBonus > yMyTank - bonusHeight && yBonus < yMyTank + myTankHeight)
            {
                if (typeid(*bonus) == typeid(BonusTank) && myTank->getHealth() <= MAX_LIFE_COUNT)
                    myTank->increaseHealth();

                else if (typeid(*bonus) == typeid(BonusStar))
                {
                    myTank->levelUp();
                    switch (myTank->getLevel())
                    {
                        case 1:
                            myTank->setBulletSpeed(6);
                            break;
                        case 2:
                            myTank->getBullets().push_back(new Bullet(xMyTank, yMyTank));
                            movingObjects.insert(std::next(movingObjectIter, 1), myTank->getBullets().back());
                            myTank->setBulletSpeed(6);
                            break;
                        case 3:
                            myTank->setPowerBullets(true);
                            break;
                        default:
                            myTank->setLevel(3);
                    }
                }

                bonus->isActive() = false;
            }
        }
    }

//    there we detect the collisions of moving object to other moving objects
    std::vector<MovingObject*>::iterator nextMovingObjectIter;
//    there we move iterator of the next object. And if this object is a tank, we move the
//    iterator to the number of bullets so the tank can't accidentally destroy itself
    if (typeid(*movingObject) == typeid(MyTank) || typeid(*movingObject) == typeid(EnemyTank))
        // nextMovingObjectIter = movingObjectIter + dynamic_cast<Tank*>(movingObject)->getBullets().size();
        nextMovingObjectIter = std::next(movingObjectIter, dynamic_cast<Tank*>(movingObject)->getBullets().size() + 1);
    else if (typeid(*movingObject) == typeid(Bullet))
        nextMovingObjectIter = std::next(movingObjectIter, 1);

    for (; nextMovingObjectIter != movingObjects.end(); ++nextMovingObjectIter)
    {
        if (*movingObjectIter == nullptr) continue;
        if (!(*movingObjectIter)->isActive()) continue;
        if (*nextMovingObjectIter == nullptr) continue;
        if (!(*nextMovingObjectIter)->isActive()) continue;

        MovingObject *nextMovObj = *nextMovingObjectIter;

        nextMovObj->getParameters(xAnotherObj, yAnotherObj, widthAnotherObj, heightAnotherObj, dirAnotherObj);

        if (xAnotherObj > xMovObj - widthAnotherObj && xAnotherObj < xMovObj + widthMovObj &&
            yAnotherObj > yMovObj - heightAnotherObj && yAnotherObj < yMovObj + heightMovObj)
        {
            if ((typeid(*movingObject) == typeid(MyTank) || typeid(*movingObject) == typeid(EnemyTank)) &&
               (typeid(*nextMovObj) == typeid(MyTank) || typeid(*nextMovObj) == typeid(EnemyTank)))
            {
                if (dynamic_cast<Tank*>(movingObject)->keyIsPressed())
                    movingObject->handleThisObjectIfEncounteredWithAnother(nextMovObj, nullptr);

                if (xMovObj > xAnotherObj - widthMovObj && xMovObj < xAnotherObj + widthAnotherObj &&
                    yMovObj > yAnotherObj - heightMovObj && yMovObj < yAnotherObj + heightAnotherObj)
                    if (dynamic_cast<Tank*>(nextMovObj)->keyIsPressed())
                        nextMovObj->handleThisObjectIfEncounteredWithAnother(movingObject, nullptr);

            }

            else if(typeid(*movingObject) == typeid(Bullet) &&
                (typeid(*nextMovObj) == typeid(MyTank) || typeid(*nextMovObj) == typeid(EnemyTank)))
            {
                movingObject->handleThisObjectIfEncounteredWithAnother(nextMovObj, new BigBoom(xAnotherObj, yAnotherObj));
                damageTank(nextMovingObjectIter);
            }
            else if((typeid(*movingObject) == typeid(MyTank) || typeid(*movingObject) == typeid(EnemyTank)) &&
                    typeid(*nextMovObj) == typeid(Bullet))
            {
                nextMovObj->handleThisObjectIfEncounteredWithAnother(movingObject, new BigBoom(xAnotherObj, yAnotherObj));
                damageTank(movingObjectIter);
            }
            else if(typeid(*movingObject) == typeid(Bullet) && typeid(*nextMovObj) == typeid(Bullet))
            {
                movingObject->handleThisObjectIfEncounteredWithAnother(movingObject, new SmallBoom(0,0));
                nextMovObj->handleThisObjectIfEncounteredWithAnother(nextMovObj, new SmallBoom(0,0));
            }
        }
    }
}

void GameMap::damageTank(std::vector<MovingObject*>::iterator tankIter)
{
    Tank* tank = dynamic_cast<Tank*>(*tankIter);
    tank->damageTank();
    if (!tank->getHealth())
    {
        int countOfBullets = tank->getBullets().size();
        for (int i = 0; i < countOfBullets + 1; ++i)
        {
            delete *tankIter;
            *tankIter++ = nullptr;
        }
    }
    else
        tank->isActive() = false;
}