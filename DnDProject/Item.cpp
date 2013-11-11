#include "Item.h"
#include <exception>


Item::Item(std::string name, std::string description, ItemType type, Enhancements *enhancements)
{
	this->name = name;
	this->description = description;
	this->type = type;
	this->enhancements = *enhancements;
}


Item::~Item(void)
{
	delete &this->name;
	delete &this->description;
	delete &this->type;
	delete &this->enhancements;
}


std::string Item::getName(void)
{
	return this->name;
}


std::string Item::getDescription(void)
{
	return this->description;
}


ItemType Item::getType(void)
{
	return this->type;
}


Enhancements Item::getEnhancements(void)
{
	return this->enhancements;
}


int Item::getEnhancement(ItemEnhancement enhancement)
{
	return this->enhancements.at(enhancement);
}


void Item::setEnhancements(Enhancements enhancements, bool exceptionOnUndefined)
{
	// Go through each provided enhancement and make sure they're valid,
	// as in they have been defined already.
	for (Enhancements::iterator i = enhancements.begin(); i != enhancements.end(); ++i) {
		Enhancements::iterator eI = this->enhancements.find(i->first);

		// Handle undefined enhancements
		if (eI == this->enhancements.end()) {
			if (exceptionOnUndefined) throw std::exception("Specified enhancement not predefined."); // If chosen, throw an exception and get out...
			continue; // ... otherwise just skip this one.
		}

		eI->second = i->second;
	}
}


void Item::setEnhancement(ItemEnhancement enhancement, int value)
{
	Enhancements::iterator eI = this->enhancements.find(enhancement);

	// Handle undefined enhancements
	if (eI == this->enhancements.end())
		throw std::exception("Specified enhancement not predefined."); // Throw an appropriately worded exception.

	eI->second = value;
}