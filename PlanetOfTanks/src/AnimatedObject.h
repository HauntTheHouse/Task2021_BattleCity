//
// Created by durda on 2/15/21.
//

#ifndef PLANETOFTANKS_ANIMATEDOBJECT_H
#define PLANETOFTANKS_ANIMATEDOBJECT_H

#include "Object.h"

class AnimatedObject : public Object {
protected:
    std::vector<Sprite*> images;

    unsigned int duration;
    unsigned int startTiming;
    unsigned int frequency;
public:
    AnimatedObject(int xpos, int ypos) : Object(xpos, ypos), duration(300), startTiming(lastFrame), frequency(0) {}
//    ~AnimatedObject() override
//    {
//        for (auto image : images)
//            destroySprite(image);
//    }

    virtual void resetTiming() { startTiming = lastFrame; }
};




#endif //PLANETOFTANKS_ANIMATEDOBJECT_H
