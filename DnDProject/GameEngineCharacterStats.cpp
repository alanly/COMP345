#include "GameEngineCharacterStats.h"
#include <iostream>
#include <sstream>


GameEngineCharacterStats::GameEngineCharacterStats(LoaderParameters* parameters, Character* character) : GameObject(parameters)
{
	this->character = character;
}


GameEngineCharacterStats::~GameEngineCharacterStats(void)
{
}
void GameEngineCharacterStats::handleMainEvents()
{

}
void GameEngineCharacterStats::draw()
{
	// Retrieve starting positions
	int x = this->getParameters()->getXPos();
	int y = this->getParameters()->getYPos();

	// Draw Character Level
	std::ostringstream convert;
	convert << this->character->getLevel();
	std::string levelMsg = "Current Level: " + convert.str();

	GameObject* levelGameObj = new GameObject(new LoaderParameters(x,y,300,25,0,0,levelMsg));
	SDL_Color color = {255,255,0};
	TextureManager::getInstance()->loadFont(levelGameObj->getParameters()->getId(), Game::getInstance()->getRenderer(), levelGameObj->getParameters()->getId(), color);
	levelGameObj->draw();
	y += 25;


	// Draw Character HP
		// No consistent way to determine maximum HP.

	// Draw Character Equipped Items
	std::vector<Item*> characterEquipped = std::vector<Item*>();

	characterEquipped.push_back(this->character->getHelmet());
	characterEquipped.push_back(this->character->getArmor());
	characterEquipped.push_back(this->character->getShield());
	characterEquipped.push_back(this->character->getWeapon());
	characterEquipped.push_back(this->character->getRing1());
	characterEquipped.push_back(this->character->getRing2());
	characterEquipped.push_back(this->character->getBoots());
	characterEquipped.push_back(this->character->getBelt());

	for (std::vector<Item*>::iterator cIt = characterEquipped.begin(); cIt != characterEquipped.end(); ++cIt) {
		if (*cIt != nullptr) {
			GameObject* itemGameObj = new GameObject(new LoaderParameters(x, y, 300, 25, 0, 0, (*cIt)->getName()));
			SDL_Color color = {255, 255, 0};
			TextureManager::getInstance()->loadFont(itemGameObj->getParameters()->getId(), Game::getInstance()->getRenderer(), itemGameObj->getParameters()->getId(), color);
			itemGameObj->draw();
			y += 25;
		}
	}

	if (y == this->getParameters()->getYPos() + 25) {
		GameObject* itemGameObj = new GameObject(new LoaderParameters(x, y, 300, 25, 0, 0, "No Items Equipped"));
		SDL_Color color = {255, 255, 0};
		TextureManager::getInstance()->loadFont(itemGameObj->getParameters()->getId(), Game::getInstance()->getRenderer(), itemGameObj->getParameters()->getId(), color);
		itemGameObj->draw();
	}
}
void GameEngineCharacterStats::loadTextures()
{
	
}
void GameEngineCharacterStats::setCharacter(Character* character)
{
	this->character = character;
}