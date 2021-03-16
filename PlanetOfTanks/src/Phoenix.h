//
// Created by durda on 2/18/21.
//

#ifndef PLANETOFTANKS_PHOENIX_H
#define PLANETOFTANKS_PHOENIX_H

#include "Object.h"

class Phoenix : public Object
{
private:
    std::vector<Sprite*> schrodingerImage;
public:
    Phoenix(int xpos, int ypos) : Object(xpos, ypos)
    {
        active = true;
        schrodingerImage.push_back(createSprite("../images/Phoenix_Active.png"));
        schrodingerImage.push_back(createSprite("../images/Phoenix_Inactive.png"));

        getSpriteSize(schrodingerImage.front(), width, height);
    }
    void draw() override
    {
        if (active)
            drawSprite(schrodingerImage.front(), x, y);
        else
            drawSprite(schrodingerImage.back(), x, y);
    }
};


#endif //PLANETOFTANKS_PHOENIX_H
