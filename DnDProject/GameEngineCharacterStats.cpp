#include "GameEngineCharacterStats.h"
#include <iostream>
#include <string>


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

	// Draw Character HP
	std::string hpMsg = "HP: " + to_string(this->character->getCurrentHitPoints()) + "/" + to_string(this->character->getMaxHitPoints());
	
	float hpPercent = (float)this->character->getCurrentHitPoints() / this->character->getMaxHitPoints();

	SDL_Color green = {0,255,0};
	SDL_Color orange = {255,165,0};
	SDL_Color red = {255,0,0};

	SDL_Color *hpColor = new SDL_Color(green);

	if (hpPercent < 0.75) hpColor = new SDL_Color(orange);

	if (hpPercent < 0.25) hpColor = new SDL_Color(red);

	GameObject* hpGameObj = new GameObject(new LoaderParameters(x,y,300,25,0,0,hpMsg));
	TextureManager::getInstance()->loadFont(hpGameObj->getParameters()->getId(), Game::getInstance()->getRenderer(), hpGameObj->getParameters()->getId(), *hpColor);
	hpGameObj->draw();
	y += 25;

	// Draw Character Level
	std::string levelMsg = "Level: " + to_string(this->character->getLevel());

	GameObject* levelGameObj = new GameObject(new LoaderParameters(x,y,300,25,0,0,levelMsg));
	SDL_Color color = {255,255,0};
	TextureManager::getInstance()->loadFont(levelGameObj->getParameters()->getId(), Game::getInstance()->getRenderer(), levelGameObj->getParameters()->getId(), color);
	levelGameObj->draw();
	y += 25;

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