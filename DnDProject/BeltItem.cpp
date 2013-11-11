#include "BeltItem.h"


BeltItem::BeltItem(std::string name, std::string description, int constitution, int strength) :
	Item(name, description, ItemType::BELT, new Enhancements())
{
	this->setupEnhancements(constitution, strength);
}


BeltItem::BeltItem(std::string name, std::string description) :
	Item(name, description, ItemType::BELT, new Enhancements())
{
	this->setupEnhancements(0,0);
}


BeltItem::~BeltItem()
{
}


void BeltItem::setupEnhancements(int constitution, int strength)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::CONSTITUTION, constitution) );
	this->enhancements.insert( Enhancement(ItemEnhancement::STRENGTH, strength) );
}