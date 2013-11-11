#include "ShieldItem.h"


ShieldItem::ShieldItem(std::string name, std::string description, int armourClass) :
	Item(name, description, ItemType::SHIELD, new Enhancements())
{
	this->setupEnhancements(armourClass);
}


ShieldItem::ShieldItem(std::string name, std::string description) :
	Item(name, description, ItemType::SHIELD, new Enhancements())
{
	this->setupEnhancements(0);
}


ShieldItem::~ShieldItem(void)
{
}


void ShieldItem::setupEnhancements(int armourClass)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::ARMOUR_CLASS, armourClass) );
}