#include "GameEngineSideBar.h"


GameEngineSideBar::GameEngineSideBar(LoaderParameters* parameters, Character* character) : GameObject(parameters)
{
	this->character = character;
	loadTextures();
	this->charItemView = new GameEngineCharacterItems(new LoaderParameters(parameters->getXPos(), parameters->getYPos(), 300, 32, 0, 0, ""), character);
	this->charStatsView = new GameEngineCharacterStats(new LoaderParameters(parameters->getXPos(), parameters->getYPos()+300, 300, 25, 0, 0, ""), character);
}


GameEngineSideBar::~GameEngineSideBar(void)
{

}

void GameEngineSideBar::handleMainEvents()
{
	charItemView->handleMainEvents();
	charStatsView->handleMainEvents();
}
void GameEngineSideBar::draw()
{
	charItemView->draw();
	charStatsView->draw();
}
void GameEngineSideBar::loadTextures()
{
	
}
void GameEngineSideBar::setCharacter(Character* character)
{
	this->character = character;
	charItemView->setCharacter(character);
	charStatsView->setCharacter(character);
}