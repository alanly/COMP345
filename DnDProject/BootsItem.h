#pragma once
#include "item.h"


/**
 * Represents a Boot object.
 */
class BootsItem :
	public Item
{
private:
	void setupEnhancements(int armourClass, int dexterity);
public:
	BootsItem(std::string name, std::string description, int armourClass, int dexterity);
	BootsItem(std::string name, std::string description);
	~BootsItem(void);
};

