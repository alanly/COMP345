#pragma once
#include "Entity.h"
#include "HelmetItem.h"
#include "ArmourItem.h"
#include "ShieldItem.h"
#include "WeaponItem.h"
#include "RingItem.h"
#include "BootsItem.h"
#include "BeltItem.h"
#include "tinyxml2.h"
using namespace tinyxml2;
const int levelExpModifier = 50;

class Character : public Entity
{
	private:
		void levelUp();
		int currentExp, expAtLevel;
		enumUtility::characterClassifiction classification;
		HelmetItem *helmet;
		ArmourItem *armor;
		ShieldItem *shield;
		WeaponItem *weapon;
		RingItem *ring1;
		RingItem *ring2;
		BootsItem *boots;
		BeltItem *belt;
		//XMLHandle* convertItemToXML(Item* item,XMLNode* itemNode);
	public:
		Character(string, int);
		Character(string, int, enumUtility::characterClassifiction);
		~Character(void);
		void gainExperiance(int exp);
		
		//getters
		enumUtility::characterClassifiction getClassification();
		HelmetItem* getHelmet();
		ArmourItem* getArmor();
		WeaponItem* getWeapon();
		ShieldItem* getShield();
		RingItem* getRing1();
		RingItem* getRing2();
		BootsItem* getBoots();
		BeltItem* getBelt();

		//setters
		void setHelmet(HelmetItem* helmet);
		void setArmor(ArmourItem* armor);
		void setWeapon(WeaponItem* weap);
		void setShield(ShieldItem* shield);
		void setRing1(RingItem* ring);
		void setRing2(RingItem* ring);
		void setBoots(BootsItem* boots);
		void setBelt(BeltItem* belt);
		void setClassification(enumUtility::characterClassifiction);
		void saveToFile();
		void readFromFile(string filename);
};

