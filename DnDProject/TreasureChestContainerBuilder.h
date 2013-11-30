#pragma once
#include "containerbuilder.h"
#include <Windows.h>
#include "ItemFactory.h"

class TreasureChestContainerBuilder :
	public ContainerBuilder
{
private:
	void populateContainer()
	{
		int _max_container_size = 6;

		for (int i = 0; i < _max_container_size; ++i) {
			this->container->addItem(ItemFactory::getInstance()->createRandomItem());
		}
	}

public:

	TreasureChestContainerBuilder(void)
	{
	}

	~TreasureChestContainerBuilder(void)
	{
	}

	void buildContainer()
	{
		this->container = new Container(ContainerType::TREASURE_CHEST);
		this->populateContainer();
	}

};

