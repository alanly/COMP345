#include "GameEngineCharacterItems.h"
#include <iostream>

GameEngineCharacterItems::GameEngineCharacterItems(LoaderParameters* parameters, Character* character) : GameObject(parameters)
{
	this->character = character;
}

GameEngineCharacterItems::~GameEngineCharacterItems(void)
{
}
void GameEngineCharacterItems::handleMainEvents()
{

}
void GameEngineCharacterItems::draw()
{
	int x = this->getParameters()->getXPos();
	int y = this->getParameters()->getYPos();
	vector<Item*> tempItems = character->getItems();
	for(vector<Item*>::const_iterator iter = tempItems.begin(); iter != tempItems.end(); ++iter)
	{
		if(*iter != 0)
        {
			GameObject* gameObj = new GameObject(new LoaderParameters(x, y, 300, 25, 0, 0, (*iter)->getName()));
			SDL_Color  color = {255,255,0};
			TextureManager::getInstance()->loadFont(gameObj->getParameters()->getId(),Game::getInstance()->getRenderer(), gameObj->getParameters()->getId(), color);
			gameObj->draw();
			items.push_back(gameObj);
			y += 25;
		}

	}
}
void GameEngineCharacterItems::loadTextures()
{
	
}
void GameEngineCharacterItems::setCharacter(Character* character)
{
	this->character = character;
}