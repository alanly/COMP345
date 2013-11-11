#include "ArmourItem.h"


ArmourItem::ArmourItem(std::string name, std::string description, int armourClass) :
	Item(name, description, ItemType::ARMOUR, new Enhancements())
{
	this->setupEnhancements(armourClass);
}


ArmourItem::ArmourItem(std::string name, std::string description) :
	Item(name, description, ItemType::ARMOUR, new Enhancements())
{
	this->setupEnhancements(0);
}


ArmourItem::~ArmourItem(void)
{
}


void ArmourItem::setupEnhancements(int armourClass)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::ARMOUR_CLASS, armourClass) );
}