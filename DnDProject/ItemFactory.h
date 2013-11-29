#pragma once
#include "Item.h"
#include "Random.h"
#include <string>
#include "ArmourItem.h"
#include "BeltItem.h"
#include "BootsItem.h"
#include "HelmetItem.h"
#include "RingItem.h"
#include "ShieldItem.h"
#include "WeaponItem.h"

class ItemFactory
{
private:
	static ItemFactory* instance;

	int getRandomEnhancementValue()
	{
		return Random::getRandomInt(1,5);
	}

public:

	static ItemFactory* getInstance()
	{
		return instance;
	}

	Item* createRandomItem()
	{
		std::string itemTypes[8] = {"Armour", "Belt", "Boots", "Helmet", "Ring", "Shield", "Weapon"};
		std::string type = itemTypes[Random::getRandomInt(0,7)];
		
		if (type == "Armour")
			return new ArmourItem(type, "", getRandomEnhancementValue());

		if (type == "Belt")
			return new BeltItem(type, "", getRandomEnhancementValue(), getRandomEnhancementValue());

		if (type == "Boots")
			return new BootsItem(type, "", getRandomEnhancementValue(), getRandomEnhancementValue());

		if (type == "Helmet")
			return new HelmetItem(type, "", getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue());

		if (type == "Ring")
			return new RingItem(type, "", getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue());

		if (type == "Shield")
			return new ShieldItem(type, "", getRandomEnhancementValue());

		if (type == "Weapon")
			return new WeaponItem((Random::getRandomInt(0,1) == 1 ? "Sword" : "Bow"), "", getRandomEnhancementValue(), getRandomEnhancementValue());

		return nullptr;
	}

};

