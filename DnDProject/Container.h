#pragma once
#include <vector>
#include "Item.h"
#include "ContainerType.h"
typedef std::vector<Item *> ItemList;


/**
 * The container holds multiple instances of Item.
 */
class Container
{
private:
	ContainerType type;
	ItemList *items;
public:
	Container(ContainerType type);
	Container(ContainerType type, ItemList *initialItems);
	~Container(void);
	ContainerType getType(void);
	ItemList getItems(void);
	Item* getItem(int position);
	void addItem(Item *item);
	void removeItem(int position);
	void removeItem(Item *item);
	bool hasItems(void);
};

