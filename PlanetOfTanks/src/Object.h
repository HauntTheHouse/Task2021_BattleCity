#ifndef OBJECT_H
#define OBJECT_H

#include "../../Framework/inc/Framework.h"
#include <iostream>
#include <fstream>
#include <vector>

extern unsigned int lastFrame;
extern unsigned int deltaTime;
extern unsigned int accurateTickCount;


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

enum ObjectDirection
{
    RIGHT,
    LEFT,
    DOWN,
    UP
};

class Object
{
protected:
    int x, y;
    int width, height;

    bool active;
public:
    Object(int xpos, int ypos) : x(xpos), y(ypos), width(0), height(0), active(false) {}
//    virtual ~Object() = default;

    virtual void setPosition(int xpos, int ypos) {x = xpos; y = ypos;}
    virtual void getParameters (int &xpos, int &ypos, int &objWidth, int &objHeight)
    { xpos = x; ypos = y; objWidth = width; objHeight = height; }
    virtual bool& isActive() { return active; }
    virtual void draw() = 0;
};





#endif //OBJECT_H
