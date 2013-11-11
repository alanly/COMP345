#pragma once
#include <string>
#include <map>
#include <vector>
#include "Enum_Utility.h"
#include "Item.h"
#include "Dice.h"
#include <algorithm>
using namespace std;

class Entity
{
	private:
		string name;
		map<enumUtility::abilityModifer,int> stats;
		vector<Item*> inventory;
		void initializeStats();
	protected:
		int level;
		int currentHitPoints, maxHitPoints;
	public:
		Entity(void);
		~Entity(void);
		Entity(string name, int level);
		bool takeDamage(int dmg);

		string getName();
		void setName(string);
		int getLevel();
		void addItemToInventory(Item* item);
		void removeItemFromInventory(Item* item);
		//getters
		int getStrength();
		int getDexterity();
		int getCharisma();
		int getInteligence();
		int getConstitution();
		int getWisdom();

		int getArmorClass();
		int getDamageBonus();
		int getAttackBonus();
};

