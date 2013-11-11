#include "Container.h"
#include <algorithm>


Container::Container(ContainerType type)
{
	this->type = type;
	this->items = new ItemList();
}


Container::Container(ContainerType type, ItemList *initialItems)
{
	this->type = type;
	this->items = initialItems;
}


Container::~Container(void)
{
	delete &this->type;
	delete this->items;
}


ContainerType Container::getType(void)
{
	return this->type;
}


ItemList Container::getItems(void)
{
	return *this->items;
}


Item* Container::getItem(int position)
{
	return this->items->at(position);
}


void Container::addItem(Item *item)
{
	this->items->push_back(item);
}


void Container::removeItem(int position)
{
	this->items->erase(this->items->begin() + position);
}


void Container::removeItem(Item *item)
{
	std::remove(this->items->begin(), this->items->end(), item);
}


bool Container::hasItems(void)
{
	return !(this->items->empty());
}