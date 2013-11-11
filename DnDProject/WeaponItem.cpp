#include "WeaponItem.h"


WeaponItem::WeaponItem(std::string name, std::string description, int attackBonus, int damageBonus) :
	Item(name, description, ItemType::WEAPON, new Enhancements())
{
	this->setupEnhancements(attackBonus, damageBonus);
}


WeaponItem::WeaponItem(std::string name, std::string description) :
	Item(name, description, ItemType::WEAPON, new Enhancements())
{
	this->setupEnhancements(0,0);
}


WeaponItem::~WeaponItem(void)
{
}


void WeaponItem::setupEnhancements(int attackBonus, int damageBonus)
{
	this->enhancements.insert( Enhancement(ItemEnhancement::ATTACK_BONUS, attackBonus) );
	this->enhancements.insert( Enhancement(ItemEnhancement::DAMAGE_BONUS, damageBonus) );
}