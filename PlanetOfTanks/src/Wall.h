//
// Created by durda on 2/14/21.
//

#ifndef PROJECT2_WALL_H
#define PROJECT2_WALL_H

#include "Object.h"

class Wall : public Object
{
protected:
    Sprite *object;
    bool breakable;
public:
    Wall(int xpos, int ypos) : Object(xpos, ypos), breakable(false) { }
//    ~Wall() override { destroySprite(object); }
    bool& getBreakable() {return breakable;}
    void draw() override = 0;
};

class BrickWall : public Wall
{
public:
    BrickWall(int xpos, int ypos);
    void draw() override;
};

class SteelWall : public Wall
{
public:
    SteelWall(int xpos, int ypos);
    void draw() override;
};

#endif //PROJECT2_WALL_H
