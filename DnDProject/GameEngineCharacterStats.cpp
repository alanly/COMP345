#include "GameEngineCharacterStats.h"


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
	std::vector<Item*> characterEquipped = std::vector<Item*>();

	characterEquipped.push_back(this->character->getHelmet());
	characterEquipped.push_back(this->character->getArmor());
	characterEquipped.push_back(this->character->getShield());
	characterEquipped.push_back(this->character->getWeapon());
	characterEquipped.push_back(this->character->getRing1());
	characterEquipped.push_back(this->character->getRing2());
	characterEquipped.push_back(this->character->getBoots());
	characterEquipped.push_back(this->character->getBelt());

	int x = this->getParameters()->getXPos();
	int y = this->getParameters()->getYPos();

	for (std::vector<Item*>::iterator cIt = characterEquipped.begin(); cIt != characterEquipped.end(); ++cIt) {
		if (*cIt != nullptr) {
			GameObject* itemGameObj = new GameObject(new LoaderParameters(x, y, 300, 25, 0, 0, (*cIt)->getName()));
			SDL_Color color = {255, 255, 0};
			TextureManager::getInstance()->loadFont(itemGameObj->getParameters()->getId(), Game::getInstance()->getRenderer(), itemGameObj->getParameters()->getId(), color);
			itemGameObj->draw();
			y += 25;
		}
	}

	if (y == this->getParameters()->getYPos()) {
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