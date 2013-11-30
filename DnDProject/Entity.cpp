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
	this->attackBonus = Dice::roleTenSideDice() + stats[enumUtility::Strength] + stats[enumUtility::Dexterity];
	this->damageBonus =  Dice::roleTenSideDice() + stats[enumUtility::Strength];
	this->armorClass =  Dice::roleTenSideDice() + stats[enumUtility::Dexterity];
	this->numberOfAttacks = (this->level / 5) + 1;
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
void Entity::setLevel(int level){
	this->level = level;
	this->numberOfAttacks = (this->level / 5) + 1;
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
	return  this->armorClass;
}

int Entity::getDamageBonus()
{
	return this->damageBonus;
}

int Entity::getAttackBonus()
{
	int temp = 0;
	int less = 0;
	for(int i = 0; i<this->numberOfAttacks;i++)
	{
		temp += (this->level - less);
		less += 5;
	}

	return (this->attackBonus * 4) + temp;
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
vector<Item*> Entity::getItems(){
	return this->inventory;
}
int Entity::getLevel(){
	return this->level;
}
void Entity::setStatistics(map<enumUtility::abilityModifer,int> stats)
{
	this->stats[enumUtility::Strength] = stats[enumUtility::Strength];
	this->stats[enumUtility::Dexterity] = stats[enumUtility::Dexterity];
	this->stats[enumUtility::Charisma] = stats[enumUtility::Charisma];
	this->stats[enumUtility::Constitution] = stats[enumUtility::Constitution];
	this->stats[enumUtility::Wisdom] = stats[enumUtility::Wisdom];
	this->stats[enumUtility::Inteligence] = stats[enumUtility::Inteligence];
}
void Entity::setStrength(int strength)
{
        this->stats[enumUtility::Strength] = strength;
}

void Entity::setDexterity(int dexterity)
{
        this->stats[enumUtility::Dexterity] = dexterity;
}

void Entity::setCharisma(int charisma)
{
        this->stats[enumUtility::Charisma] = charisma;
}

void Entity::setIntelligence(int intelligence)
{
        this->stats[enumUtility::Inteligence] = intelligence;
}

void Entity::setConstitution(int constitution)
{
        this->stats[enumUtility::Constitution] = constitution;
}

void Entity::setWisdom(int wisdom)
{
        this->stats[enumUtility::Wisdom] = wisdom;
}
int Entity::getNumberOfAttacks(){
	return this->numberOfAttacks;
}