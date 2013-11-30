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
#include <map>

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

	Item* createArmour()
	{
		std::map<int, std::string> armours;

		armours[1] = "Padded";
		armours[2] = "Leather";
		armours[3] = "Studded Leather";
		armours[4] = "Chain Mail";
		armours[5] = "Breast Plate";
		armours[6] = "Banded Mail";
		armours[7] = "Half-Plate";
		armours[8] = "Full-Plate";

		std::map<int, std::string>::iterator armourIterator = armours.begin();
		for (int i = 1; i < Random::getRandomInt(0,7); ++i) ++armourIterator; // This is a terrible idea. But I'm tired and I don't want to get up to make coffee.

		return new ArmourItem(armourIterator->second, "", armourIterator->first);
	}

	Item* createBelt()
	{
		return new BeltItem("Belt", "", getRandomEnhancementValue(), getRandomEnhancementValue());
	}

	Item* createBoots()
	{
		return new BootsItem("Boots", "", getRandomEnhancementValue(), getRandomEnhancementValue());
	}

	Item* createHelmet()
	{
		return new HelmetItem("Helmet", "", getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue());
	}

	Item* createRing()
	{
		return new RingItem("Ring", "", getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue(), getRandomEnhancementValue());
	}

	Item* createShield()
	{
		std::map<int, std::string> shields;

		shields[1] = "Buckler";
		shields[2] = "Heavy Shield";
		shields[4] = "Tower Shield";

		std::map<int, std::string>::iterator shieldsIterator = shields.begin();
		for (int i = 1; i < Random::getRandomInt(0,2); ++i) ++shieldsIterator;

		return new ShieldItem(shieldsIterator->second, "", shieldsIterator->first);
	}

	Item* createWeapon()
	{
		std::map<int, std::string> weapons;

		weapons[0] = "Long-Bow";
		weapons[Random::getRandomInt(1,5)] = "Long-Sword";

		std::map<int, std::string>::iterator weaponsIterator = weapons.begin();
		for (int i = 1; i < Random::getRandomInt(0,1); ++i) ++weaponsIterator;

		return new WeaponItem(weaponsIterator->second, "", getRandomEnhancementValue(), weaponsIterator->first);
	}

};

