#include "GameEngineSideBar.h"


GameEngineSideBar::GameEngineSideBar(LoaderParameters* parameters, Character* character) : GameObject(parameters)
{
	this->character = character;
	loadTextures();
}


GameEngineSideBar::~GameEngineSideBar(void)
{

}

void GameEngineSideBar::handleMainEvents()
{

}
void GameEngineSideBar::draw()
{
	charItemView->draw();
	charStatsView->draw();
}
void GameEngineSideBar::loadTextures()
{
	
}
