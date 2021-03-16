//
// Created by durda on 2/15/21.
//

#ifndef PLANETOFTANKS_STARTEDANIMATION_H
#define PLANETOFTANKS_STARTEDANIMATION_H

#include "AnimatedObject.h"

class StartedAnimation : public AnimatedObject {
public:
    StartedAnimation(int xpos, int ypos);
    void draw() override;
};

#endif //PLANETOFTANKS_STARTEDANIMATION_H
