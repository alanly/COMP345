#pragma once
#include "item.h"


/**
 * Represents a Belt object.
 */
class BeltItem :
	public Item
{
private:
	void setupEnhancements(int constitution, int strength);
public:
	BeltItem(std::string name, std::string description, int constitution, int strength);
	BeltItem(std::string name, std::string description);
	~BeltItem(void);
};

