#include "Game.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (Game::getInstance()->init("Dungeons And Dragons", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, 0))
	{
		Game::getInstance()->setCurrentView(enumUtility::Main_Menu);
		cout << "Game->init: success\n";
		while (Game::getInstance()->isRunning())
		{
			Game::getInstance()->handleEvents();
			Game::getInstance()->render();

			SDL_Delay(10);
		}
	}
	else
	{
		cout << "Game->init: fail\n";
		return -1;
	}

	Game::getInstance()->clean();

	return 0;
}
