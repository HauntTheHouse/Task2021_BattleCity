//
// Created by durda on 2/15/21.
//

#include "StartedAnimation.h"

StartedAnimation::StartedAnimation(int xpos, int ypos) : AnimatedObject(xpos, ypos)
{
    active = true;
    duration = 2000;
    images.push_back(createSprite("../images/Star_3.png"));
    images.push_back(createSprite("../images/Star_2.png"));
    images.push_back(createSprite("../images/Star_1.png"));
    images.push_back(createSprite("../images/Star_0.png"));
}

void StartedAnimation::draw()
{
    if (active)
    {
        frequency = (lastFrame - startTiming) % duration;
        if (frequency < duration * 1 / 14 ||
            (frequency >= duration * 6 / 14 && frequency < duration * 7 / 14) ||
            (frequency >= duration * 12 / 14 && frequency < duration * 13 / 14))
            drawSprite(images[0], x, y);
        else if (frequency < duration * 2 / 14 ||
                 (frequency >= duration * 5 / 14 && frequency < duration * 6 / 14) ||
                 (frequency >= duration * 7 / 14 && frequency < duration * 8 / 14) ||
                 (frequency >= duration * 11 / 14 && frequency < duration * 12 / 14))
            drawSprite(images[1], x, y);
        else if (frequency < duration * 3 / 14 ||
                 (frequency >= duration * 4 / 14 && frequency < duration * 5 / 14) ||
                 (frequency >= duration * 8 / 14 && frequency < duration * 9 / 14) ||
                 (frequency >= duration * 10 / 14 && frequency < duration * 11 / 14))
            drawSprite(images[2], x, y);
        else if (frequency < duration * 4 / 14 ||
                 (frequency >= duration * 9 / 14 && frequency < duration * 10 / 14))
            drawSprite(images[3], x, y);
        else
            active = false;
    }
}
