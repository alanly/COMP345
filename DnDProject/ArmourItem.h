#pragma once
#include "item.h"


/**
 * Represents an Armour object.
 */
class ArmourItem :
	public Item
{
private:
	void setupEnhancements(int armourClass);
public:
	ArmourItem(std::string name, std::string description, int armourClass);
	ArmourItem(std::string name, std::string description);
	~ArmourItem(void);
};

