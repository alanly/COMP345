#pragma once
#include "item.h"


/** 
 * Represents a Ring object.
 */
class RingItem :
	public Item
{
private:
	void setupEnhancements(int armourClass, int strength, int constitution, int wisdom, int charisma);
public:
	RingItem(std::string name, std::string description, int armourClass, int strength, int constitution, int wisdom, int charisma);
	RingItem(std::string name, std::string description);
	~RingItem(void);
};

