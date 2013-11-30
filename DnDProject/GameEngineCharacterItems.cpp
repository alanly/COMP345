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
	for(std::map<GameObject*, Item*>::iterator obj=items.begin(); obj!=items.end(); ++obj) {
		if(obj->first->isClicked()){
			obj->first->resetClicked();
			character->removeItemFromInventory(obj->second);
			if(obj->second->getType() == ItemType::ARMOUR){
				//character->setArmor(obj->second);
				ArmourItem* armor = new ArmourItem(obj->second->getName(), obj->second->getDescription());
				armor->setEnhancements(obj->second->getEnhancements());
				character->setArmor(armor);
			}
		}
	}
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
			gameObj->handleEvents();
			items[gameObj] = *iter;
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