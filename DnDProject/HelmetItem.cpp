#include "HelmetItem.h"


HelmetItem::HelmetItem(std::string name, std::string description, int intelligence, int wisdom, int armourClass) :
	Item(name, description, ItemType::HELMET, new Enhancements())
{
	this->setupEnhancements(intelligence, wisdom, armourClass);
}


HelmetItem::HelmetItem(std::string name, std::string description) :
	Item(name, description, ItemType::HELMET, new Enhancements())
{
	this->setupEnhancements(0,0,0);
}


HelmetItem::~HelmetItem(void)
{
}


void HelmetItem::setupEnhancements(int intelligence, int wisdom, int armourClass)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::INTELLIGENCE, intelligence) );
	this->enhancements.insert( Enhancement(ItemEnhancement::WISDOM, wisdom) );
	this->enhancements.insert( Enhancement(ItemEnhancement::ARMOUR_CLASS, armourClass) );
}