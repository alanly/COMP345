#pragma once
#include "item.h"


/**
 * Represents a Shield object.
 */
class ShieldItem :
	public Item
{
private:
	void setupEnhancements(int armourClass);
public:
	ShieldItem(std::string name, std::string description, int armourClass);
	ShieldItem(std::string name, std::string description);
	~ShieldItem(void);
};

