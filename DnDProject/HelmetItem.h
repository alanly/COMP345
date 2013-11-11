#pragma once
#include "Item.h"


/**
 * Represents a Helmet object.
 */
class HelmetItem :
	public Item
{
private:
	void setupEnhancements(int intelligence, int wisdom, int armorClass);
public:
	HelmetItem(std::string name, std::string description, int intelligence, int wisdom, int armourClass);
	HelmetItem(std::string name, std::string description);
	~HelmetItem(void);
};