#include "BootsItem.h"


BootsItem::BootsItem(std::string name, std::string description, int armourClass, int dexterity) :
	Item(name, description, ItemType::BOOTS, new Enhancements())
{
	this->setupEnhancements(armourClass, dexterity);
}


BootsItem::BootsItem(std::string name, std::string description) :
	Item(name, description, ItemType::BOOTS, new Enhancements())
{
	this->setupEnhancements(0,0);
}


BootsItem::~BootsItem(void)
{
}


void BootsItem::setupEnhancements(int armourClass, int dexterity)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::ARMOUR_CLASS, armourClass) );
	this->enhancements.insert( Enhancement(ItemEnhancement::DEXTERITY, dexterity) );
}