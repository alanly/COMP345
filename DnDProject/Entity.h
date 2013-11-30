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
		int numberOfAttacks;
		int attackBonus;
		int damageBonus;
		int armorClass;
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
		void setLevel(int level);
		vector<Item*> getItems();
		void setStatistics(map<enumUtility::abilityModifer,int> stats);
		//getters
		int getStrength();
		int getDexterity();
		int getCharisma();
		int getInteligence();
		int getConstitution();
		int getWisdom();
		virtual int getArmorClass() = 0;
		int getDamageBonus();
		int getAttackBonus();

		int getNumberOfAttacks();
		 //setters
        void setStrength(int strength);
        void setDexterity(int dexterity);
        void setCharisma(int charisma);
        void setIntelligence(int intelligence);
        void setConstitution(int constitution);
        void setWisdom(int wisdom);

				void setCurrentHitPoints(int hp);
		int getCurrentHitPoints();
		int getMaxHitPoints();
		void setMaxHitPoints(int hp);
};

