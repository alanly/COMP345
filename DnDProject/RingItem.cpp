#include "RingItem.h"


RingItem::RingItem(std::string name, std::string description, int armourClass, int strength, int constitution, int wisdom, int charisma) :
	Item(name, description, ItemType::RING, new Enhancements())
{
	this->setupEnhancements(armourClass, strength, constitution, wisdom, charisma);
}


RingItem::RingItem(std::string name, std::string description) :
	Item(name, description, ItemType::RING, new Enhancements())	
{
	this->setupEnhancements(0,0,0,0,0);
}


RingItem::~RingItem(void)
{
}


void RingItem::setupEnhancements(int armourClass, int strength, int constitution, int wisdom, int charisma)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::ARMOUR_CLASS, armourClass) );
	this->enhancements.insert( Enhancement(ItemEnhancement::STRENGTH, strength) );
	this->enhancements.insert( Enhancement(ItemEnhancement::CONSTITUTION, constitution) );
	this->enhancements.insert( Enhancement(ItemEnhancement::WISDOM, wisdom) );
	this->enhancements.insert( Enhancement(ItemEnhancement::CHARISMA, charisma) );
}