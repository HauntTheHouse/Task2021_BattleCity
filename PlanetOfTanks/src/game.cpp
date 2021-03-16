#include "../../Framework/inc/Framework.h"
#include "GameMap.h"

#include <iostream>
#include <vector>
// #include <bit>

/* Test Framework realization */

unsigned int lastFrame;
unsigned int deltaTime;

unsigned int accurateTickCount;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 650;

class MyFramework : public Framework {
private:
    GameMap* gameMap;

public:

	void PreInit(int& width, int& height, bool& fullscreen) override
	{
		width = 800;
		height = 650;
		fullscreen = false;
	}

	bool Init() override {
        gameMap = new GameMap();

		return true;

	}

	void Close() override {

	}

	bool Tick() override
	{
        unsigned int currentFrame = getTickCount();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


		// std::cout << (int)(test) << std::endl;
		// if (accurateTickCount % 6 == 0)
		// {
			gameMap->processObjects();
		// }
		gameMap->draw();

		accurateTickCount++;
		return false;
	}

	void onMouseMove(int x, int y, int xrelative, int yrelative) override {

	}

	void onMouseButtonClick(FRMouseButton button, bool isReleased) override
	{
//          if my tank is not destroyed I can handle the keys
        if (MyTank* myTank = gameMap->getMyTank())
            if (button == FRMouseButton::LEFT && !isReleased  && gameMap->isActive())
//                I can have several bullets, so I need to activate only one
                for (Bullet* bullet : myTank->getBullets())
                    if  (!bullet->isActive())
                    {
                        myTank->setBulletActive(true);
                        break;
                    }
	}

	void onKeyPressed(FRKey k) override
	{
        if (MyTank* myTank = gameMap->getMyTank())
            if (gameMap->isActive())
            {
                myTank->pressKey(true);
                myTank->setDirection(static_cast<ObjectDirection>(k));
            }
    }

	void onKeyReleased(FRKey k) override
	{
        if (MyTank* myTank = gameMap->getMyTank())
            if (gameMap->isActive())
                myTank->pressKey(false);
	}

	const char* GetTitle() override
	{
		return "Planet Of Tanks";
	}

};

int main(int argc, char *argv[])
{
	run(new MyFramework);
}
