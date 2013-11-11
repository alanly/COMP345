#pragma once
#include <unordered_map>
#include "ItemType.h"
#include "ItemEnhancement.h"


typedef std::unordered_map<ItemEnhancement, int> Enhancements;
typedef std::pair<ItemEnhancement, int> Enhancement;


/**
 * The base game item class.
 */
class Item
{
protected:
	std::string name;
	std::string description;
	ItemType type;
	Enhancements enhancements;
public:
	Item(std::string name, std::string description, ItemType type, Enhancements *enhancement);
	~Item(void);
	std::string getName(void);
	std::string getDescription(void);
	ItemType getType(void);
	Enhancements getEnhancements(void);

	/**
	 * Retrieves the specified enhancement's integer value.
	 */
	int getEnhancement(ItemEnhancement enhancement);

	/**
	 * Sets multiple enhancements for the item.
	 *
	 * @enhancements an unordered map containing the appropriate enhancements and their respective values
	 * @exceptionOnUndefined determines whether or not an invalid enhancement for this item should throw an exception or be ignored
	 */
	void setEnhancements(Enhancements enhancements, bool exceptionOnUndefined = true);

	/**
	 * Sets a single enhancement and its respective value.
	 *
	 * @enhancement the relevant ItemEnhancement enum type for this item
	 * @value the value for this enhancement
	 */
	void setEnhancement(ItemEnhancement enhancement, int value);
};

