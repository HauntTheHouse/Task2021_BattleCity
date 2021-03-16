//
// Created by durda on 2/19/21.
//

#ifndef PLANETOFTANKS_RIGHTINTERFACE_H
#define PLANETOFTANKS_RIGHTINTERFACE_H

#include "Object.h"
#include <vector>
#include <string>

extern const int MAX_LIFE_COUNT;
extern const int UNIT_SIZE;
extern int enemyTanksLeftToKill;
extern int myTankLife;

class RightInterface : public Object
{
private:
    Sprite* tankSign;
    std::vector<Sprite*> lives;
    Sprite* flag;

public:
    RightInterface();
    void draw() override;
};


#endif //PLANETOFTANKS_RIGHTINTERFACE_H
