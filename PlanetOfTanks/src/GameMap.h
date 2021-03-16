//
// Created by durda on 2/13/21.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "RightInterface.h"
#include "Wall.h"
#include "Tank.h"
#include "Bullet.h"
#include "Bonus.h"
#include "Phoenix.h"

#include <vector>
#include <list>
#include <string>

const int GAMEMAP_WIDTH = 650;
const int GAMEMAP_HEIGHT = 650;

// for reading level data
enum typeOfObject
{
    EMPTY = '0',
    BRICK_WALL = '1',
    STEEL_WALL = '2'
};

class GameMap
{
private:
    bool active;

    Sprite* background;
    std::vector<Sprite*> gameOver;

    RightInterface* rightInterface;

    std::vector<Wall*> walls;
    std::vector<MovingObject*> movingObjects;     //tanks and bullets

    std::vector<Bonus*> bonuses;
    Phoenix* phoenix;

    void initWalls(const char* pathToData);
    void collisionDetection(std::vector<MovingObject*>::iterator movingObjectIter);
    void addTank(Tank *tank);
    void addBonuses();
    void damageTank(std::vector<MovingObject*>::iterator tankIter);
public:
    GameMap();
    bool& isActive() { return active; }
    MyTank* getMyTank() const;
    void processObjects();
    void draw();
};


#endif //GAMEMAP_H
