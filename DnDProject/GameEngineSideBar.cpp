#include "GameEngineSideBar.h"


GameEngineSideBar::GameEngineSideBar(LoaderParameters* parameters, Character* character) : GameObject(parameters)
{
	this->character = character;
	loadTextures();
	this->charItemView = new GameEngineCharacterItems(parameters, character);
	this->charStatsView = new GameEngineCharacterStats(parameters, character);
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
