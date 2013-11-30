#include "GameEngineCharacterItems.h"
#include <iostream>
#include "Console.h"

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
		obj->first->handleEvents();
		if(obj->first->isClicked()){
			obj->first->resetClicked();
			character->removeItemFromInventory(obj->second);
			switch(obj->second->getType()){
				case ItemType::ARMOUR:
					character->setArmor((ArmourItem*)obj->second);
					Console::getInstance()->addLine("Equiping Armor");
					break;
				case ItemType::WEAPON:
					character->setWeapon((WeaponItem*)obj->second);
					Console::getInstance()->addLine("Equiping weap");
					break;
				case ItemType::SHIELD:
					character->setShield((ShieldItem*)obj->second);
					Console::getInstance()->addLine("Equiping shield");
					break;
				case ItemType::BOOTS:
					character->setBoots((BootsItem*)obj->second);
					Console::getInstance()->addLine("Equiping boots");
					break;
				case ItemType::BELT:
					character->setBelt((BeltItem*)obj->second);
					Console::getInstance()->addLine("Equiping belt");
					break;
				case ItemType::RING:
					character->setRing1((RingItem*)obj->second);
					Console::getInstance()->addLine("Equiping ring");
					break;
				case ItemType::HELMET:
					character->setHelmet((HelmetItem*)obj->second);
					Console::getInstance()->addLine("Equiping helmet");
					break;
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