#include "Character.h"
#include <sstream>
#include <ctime>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

Character::Character(string name, int level) : Entity(name,level)
{
	this->classification = enumUtility::Fighter;
}
Character::Character(string name, int level, enumUtility::characterClassifiction classification) : Entity(name,level)
{
	this->classification = classification;
}

Character::~Character(void)
{
}
void Character::levelUp()
{
	this->level++;
	currentExp -= expAtLevel; 
	expAtLevel = levelExpModifier * this->level;
	maxHitPoints += getConstitution() + Dice::roleTenSideDice();
}
void Character::gainExperiance(int exp)
{
	currentExp += exp;
	while(currentExp >= expAtLevel)
	{
		levelUp();
	}
}

enumUtility::characterClassifiction Character::getClassification()
{
	return this->classification;
}

HelmetItem* Character::getHelmet()
{
	return helmet;
}
ArmourItem* Character::getArmor()
{
	return armor;
}
WeaponItem* Character::getWeapon()
{
	return weapon;
}
ShieldItem* Character::getShield()
{
	return shield;
}
RingItem* Character::getRing1()
{
	return ring1;
}

RingItem* Character::getRing2()
{
	return ring2;
}
BeltItem* Character::getBelt()
{
	return belt;
}

BootsItem* Character::getBoots()
{
	return boots;
}
void Character::setHelmet(HelmetItem* helmet)
{
	this->helmet = helmet;
}
void Character::setArmor(ArmourItem* armor)
{
	this->armor = armor;
}
void Character::setWeapon(WeaponItem* weapon)
{
	this->weapon = weapon;
}
void Character::setShield(ShieldItem* shield)
{
	this->shield = shield;
}
void Character::setRing1(RingItem* ring)
{
	this->ring1 = ring;
}
void Character::setRing2(RingItem* ring)
{
	this->ring2 = ring;
}
void Character::setBelt(BeltItem* belt)
{
	this->belt = belt;
}
void Character::setBoots(BootsItem* boots)
{
	this->boots = boots;
}

void Character::setClassification(enumUtility::characterClassifiction classification)
{
	this->classification = classification;
}

void Character::saveToFile()
{
	string charName = this->getName();
	HelmetItem *helmet = this->helmet;
	ArmourItem *armor = this->armor;
	ShieldItem *shield = this->shield;
	WeaponItem *weapon = this->weapon;
	RingItem *ring1 = this->ring1;
	RingItem *ring2 = this->ring2;
	BootsItem *boots = this->boots;
	BeltItem *belt = this->belt;

	XMLDocument doc;
	XMLNode *characterNode = doc.NewElement("Character");

	XMLNode *nameNode = doc.NewElement("Name");
	const char* c = charName.c_str();
	XMLText *nameText = doc.NewText(c);

	XMLNode *currentExpNode = doc.NewElement("Current Experience");
	string convert = to_string(this->currentExp);
	c = convert.c_str();
	XMLText *currentExpText = doc.NewText(c);

	XMLNode *expAtLevelNode = doc.NewElement("Experience at Level");
	convert = to_string(this->expAtLevel);
	c = convert.c_str();
	XMLText *expAtLevelText = doc.NewText(c);

	XMLNode *characterClassNode = doc.NewElement("Character Class");
	int classification = static_cast<int>(this->classification);
	convert = to_string(classification);
	c = convert.c_str();
	XMLText *characterClassText = doc.NewText(c);

	//beginning of shit
	string name;
	string description;
	ItemType type;
	Enhancements enhancements;

	XMLNode* helmetNode = doc.NewElement("Helmet");
	XMLNode* ring1Node = doc.NewElement("Ring1");
	XMLNode* ring2Node = doc.NewElement("Ring2");
	XMLNode* weaponNode = doc.NewElement("Weapon");
	XMLNode* shieldNode = doc.NewElement("Shield");
	XMLNode* armourNode = doc.NewElement("Armour");
	XMLNode* beltNode = doc.NewElement("Belt");
	XMLNode* bootsNode = doc.NewElement("Boots");

	//Helmet
	if (this->helmet != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = helmet->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = helmet->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = helmet->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = helmet->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		helmetNode->InsertEndChild(nameNode);
		helmetNode->InsertEndChild(descriptionNode);
		helmetNode->InsertEndChild(typeNode);
		helmetNode->InsertEndChild(enhancementsNode);
	}

	//Ring1
	if (this->ring1 != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = ring1->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = ring1->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = ring1->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = ring1->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		ring1Node->InsertEndChild(nameNode);
		ring1Node->InsertEndChild(descriptionNode);
		ring1Node->InsertEndChild(typeNode);
		ring1Node->InsertEndChild(enhancementsNode);
	}

	//Ring2
	if (this->ring2 != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = ring2->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = ring2->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = ring2->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = ring2->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		ring2Node->InsertEndChild(nameNode);
		ring2Node->InsertEndChild(descriptionNode);
		ring2Node->InsertEndChild(typeNode);
		ring2Node->InsertEndChild(enhancementsNode);
	}

	//Weapon
	if (this->weapon != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = weapon->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = weapon->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = weapon->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = weapon->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		weaponNode->InsertEndChild(nameNode);
		weaponNode->InsertEndChild(descriptionNode);
		weaponNode->InsertEndChild(typeNode);
		weaponNode->InsertEndChild(enhancementsNode);
	}

	//Shield
	if (this->shield != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = shield->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = shield->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = shield->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = shield->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		shieldNode->InsertEndChild(nameNode);
		shieldNode->InsertEndChild(descriptionNode);
		shieldNode->InsertEndChild(typeNode);
		shieldNode->InsertEndChild(enhancementsNode);
	}

	//Armour
	if (this->armor != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = armor->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = armor->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = armor->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = armor->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		armourNode->InsertEndChild(nameNode);
		armourNode->InsertEndChild(descriptionNode);
		armourNode->InsertEndChild(typeNode);
		armourNode->InsertEndChild(enhancementsNode);
	}

	//Belt
	if (this->belt != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = belt->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = belt->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = belt->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = belt->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		beltNode->InsertEndChild(nameNode);
		beltNode->InsertEndChild(descriptionNode);
		beltNode->InsertEndChild(typeNode);
		beltNode->InsertEndChild(enhancementsNode);
	}

	//Boots
	if (this->boots != NULL)
	{
		XMLNode *nameNode = doc.NewElement("Name");
		name = boots->getName();
		const char* c = name.c_str();
		XMLText *nameText = doc.NewText(c);
		
		XMLNode *descriptionNode = doc.NewElement("Description");
		description = boots->getDescription();
		c = description.c_str();
		XMLText *descriptionText = doc.NewText(c);

		XMLNode *typeNode = doc.NewElement("Type");
		type = boots->getType();
		int t = static_cast<int>(type);
		string convert = to_string(t);
		c = convert.c_str();
		XMLText *typeText = doc.NewText(c);


		XMLNode *enhancementsNode = doc.NewElement("Enhancements");
		XMLNode *enhancementType;
		XMLNode *enhancementValue;
		enhancements = boots->getEnhancements();
		Enhancements::iterator it;

		for (it = enhancements.begin(); it != enhancements.end(); it++)
		{
			enhancementType = doc.NewElement("Type");
			enhancementValue = doc.NewElement("Value");
			int typeText = static_cast<int>(it->first);
			int valueText = it->second;

			convert = to_string(typeText);
			c = convert.c_str();
			XMLText *eTypeText = doc.NewText(c);

			convert = to_string(valueText);
			c = convert.c_str();
			XMLText *eValueText = doc.NewText(c);

			enhancementType->InsertEndChild(eTypeText);
			enhancementValue->InsertEndChild(eValueText);
			enhancementsNode->InsertEndChild(enhancementType);
			enhancementsNode->InsertEndChild(enhancementValue);
		}

		nameNode->InsertEndChild(nameText);
		descriptionNode->InsertEndChild(descriptionText);
		typeNode->InsertEndChild(typeText);
		bootsNode->InsertEndChild(nameNode);
		bootsNode->InsertEndChild(descriptionNode);
		bootsNode->InsertEndChild(typeNode);
		bootsNode->InsertEndChild(enhancementsNode);
	}

	//helmetNode = (this->convertItemToXML(helmet,helmetNode))->ToNode();
	//cout << helmetNode->ToElement()->Value() << endl;

	nameNode->InsertEndChild(nameText);
	currentExpNode->InsertEndChild(currentExpText);
	expAtLevelNode->InsertEndChild(expAtLevelText);
	characterClassNode->InsertEndChild(characterClassText);
	characterNode->InsertEndChild(nameNode);
	characterNode->InsertEndChild(currentExpNode);
	characterNode->InsertEndChild(expAtLevelNode);
	characterNode->InsertEndChild(characterClassNode);
	characterNode->InsertEndChild(helmetNode);
	characterNode->InsertEndChild(ring1Node);
	characterNode->InsertEndChild(ring2Node);
	characterNode->InsertEndChild(weaponNode);
	characterNode->InsertEndChild(shieldNode);
	characterNode->InsertEndChild(armourNode);
	characterNode->InsertEndChild(beltNode);
	characterNode->InsertEndChild(bootsNode);
	doc.InsertEndChild(characterNode);


	time_t t = time(0);
	struct tm now;
	localtime_s(&now,&t);
	int year = now.tm_year + 1900;
	int month = now.tm_mon + 1;
	int day = now.tm_mday;
	string sYear = to_string(year);
	string sMonth = to_string(month);
	string sDay = to_string(day);
	string date = "saves\\character\\" + this->getName() + "_" + sYear + "_" + sMonth + "_" + sDay + ".xml";
	const char* filename =  date.c_str();
	
	doc.SaveFile(filename);
}
void Character::readFromFile(string filename)
{
	const char* f = filename.c_str();
	XMLDocument doc;
	doc.LoadFile(f);

	XMLElement* nameNode = doc.FirstChildElement("Character")->FirstChildElement("Name");
	this->setName(nameNode->ToElement()->GetText());

}
/*
XMLHandle* Character::convertItemToXML(Item* item,XMLNode* itemNode)
{
	string name;
	string description;
	ItemType type;
	Enhancements enhancements;

	XMLDocument doc;
	XMLNode *nameNode = doc.NewElement("Name");
	name = item->getName();
	const char* c = name.c_str();
	XMLText *nameText = doc.NewText(c);
		
	XMLNode *descriptionNode = doc.NewElement("Description");
	description = item->getDescription();
	c = description.c_str();
	XMLText *descriptionText = doc.NewText(c);

	XMLNode *typeNode = doc.NewElement("Type");
	type = item->getType();
	int t = static_cast<int>(type);
	string convert = to_string(t);
	c = convert.c_str();
	XMLText *typeText = doc.NewText(c);

	//itemNode = doc.NewElement(c);	//root type for item node THIS IS WHERE THE PROBLEM IS

	XMLNode *enhancementsNode = doc.NewElement("Enhancements");
	XMLNode *enhancementType = doc.NewElement("Type");
	XMLNode *enhancementValue = doc.NewElement("Value");
	enhancements = item->getEnhancements();
	Enhancements::iterator it;

	for (it = enhancements.begin(); it != enhancements.end(); it++)
	{
		int typeText = static_cast<int>(it->first);
		int valueText = it->second;

		convert = to_string(typeText);
		c = convert.c_str();
		XMLText *eTypeText = doc.NewText(c);

		convert = to_string(valueText);
		c = convert.c_str();
		XMLText *eValueText = doc.NewText(c);

		enhancementType->InsertEndChild(eTypeText);
		enhancementValue->InsertEndChild(eValueText);
		enhancementsNode->InsertEndChild(enhancementType);
		enhancementsNode->InsertEndChild(enhancementValue);
	}

	nameNode->InsertEndChild(nameText);
	descriptionNode->InsertEndChild(descriptionText);
	typeNode->InsertEndChild(typeText);
	itemNode->InsertEndChild(nameNode);
	itemNode->InsertEndChild(descriptionNode);
	itemNode->InsertEndChild(typeNode);
	itemNode->InsertEndChild(enhancementsNode);
	//if (itemNode->FirstChildElement() != NULL)
	//cout << itemNode->FirstChildElement()->GetText() << endl;
	//cout << itemNode->FirstChildElement()->NextSiblingElement()->GetText() << endl;
	//cout << itemNode->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->GetText() << endl;
	//cout << itemNode->ToElement()->Value() << endl;

		XMLHandle* returnNode = new XMLHandle(itemNode);

	return returnNode;
}*/