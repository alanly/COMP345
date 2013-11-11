#pragma once
#include "item.h"


/**
 * Represents a Weapon object.
 */
class WeaponItem :
	public Item
{
private:
	void setupEnhancements(int attackBonus, int damageBonus);
public:
	WeaponItem(std::string name, std::string description, int attackBonus, int damageBonus);
	WeaponItem(std::string name, std::string description);
	~WeaponItem(void);
};

