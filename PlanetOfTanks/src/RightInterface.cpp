//
// Created by durda on 2/19/21.
//

#include "RightInterface.h"

RightInterface::RightInterface() : Object(650, 0)
{
    width = 150; height = 800;

    tankSign = createSprite("../images/Tank_Left_Sign.png");

    for (int i = 0; i < MAX_LIFE_COUNT + 1; ++i)
    {
        std::string path = "../images/" + std::to_string(i) + ".png";
        lives.push_back(createSprite(path.c_str()));
    }

    flag = createSprite("../images/Flag.png");
}

void RightInterface::draw()
{
    int xFirstPos = x + 2*UNIT_SIZE, xSecondPos = xFirstPos + UNIT_SIZE;

    int yPos = 2*UNIT_SIZE;

    for (int i = 0; i < enemyTanksLeftToKill; ++i)
    {
        if (i%2==0)
        {
            drawSprite(tankSign, xFirstPos, yPos);
        }
        if (i%2==1)
        {
            drawSprite(tankSign, xSecondPos, yPos);
            yPos += UNIT_SIZE;
        }

    }

    yPos = 2*UNIT_SIZE + 10*UNIT_SIZE + 2*UNIT_SIZE;
    drawSprite(flag, xFirstPos, yPos);

    yPos += 2*UNIT_SIZE;

    drawSprite(lives[myTankLife], xSecondPos, yPos);
}
