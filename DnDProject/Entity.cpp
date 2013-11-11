#include "Entity.h"
#include <Windows.h>


Entity::Entity(void)
{
}
Entity::~Entity(void)
{
}
Entity::Entity(string name, int level)
{
	this->name = name;
	this->level = level;
	initializeStats();
}
void Entity::initializeStats()
{
	srand(GetTickCount());
	this->stats[enumUtility::Strength] = Dice::roleTenSideDice();
	this->stats[enumUtility::Dexterity] = Dice::roleTenSideDice();
	this->stats[enumUtility::Charisma] = Dice::roleTenSideDice();
	this->stats[enumUtility::Constitution] = Dice::roleTenSideDice();
	this->stats[enumUtility::Inteligence] = Dice::roleTenSideDice();
	this->stats[enumUtility::Wisdom] = Dice::roleTenSideDice();
}

bool Entity::takeDamage(int dmg)
{
	int value = dmg - getArmorClass();
	if(value > 0)
	{
		currentHitPoints -= value;
		if(currentHitPoints <= 0)
		{
			return true;
		}
	}
	return false;
}
void Entity::addItemToInventory(Item* item)
{
	inventory.push_back(item);
}
void Entity::removeItemFromInventory(Item* item)
{
	inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());   
}

int Entity::getArmorClass()
{
	return  Dice::roleTenSideDice() + stats[enumUtility::Dexterity];	
}

int Entity::getDamageBonus()
{
	return  Dice::roleTenSideDice() + stats[enumUtility::Strength];
}
int Entity::getAttackBonus()
{
	return Dice::roleTenSideDice() + stats[enumUtility::Strength] + stats[enumUtility::Dexterity];
}

/*
	returns the ability modifier "Strength"
*/
int Entity::getStrength()
{
	return stats[enumUtility::Strength];
}
/*
	returns the ability modifier "Dexterity"
*/
int Entity::getDexterity()
{
	return stats[enumUtility::Dexterity];
}
/*
	returns the ability modifier "Charisma"
*/
int Entity::getCharisma()
{
	return stats[enumUtility::Charisma];
}
/*
	returns the ability modifier "Inteligence"
*/
int Entity::getInteligence()
{
	return stats[enumUtility::Inteligence];
}
/*
	returns the ability modifier "Constitution"
*/
int Entity::getConstitution()
{
	return stats[enumUtility::Constitution];
}
/*
	returns the ability modifier "Wisdom"
*/
int Entity::getWisdom()
{
	return stats[enumUtility::Wisdom];
}

string Entity::getName()
{
	return this->name;
}

void Entity::setName(string name)
{
	this->name = name;
}