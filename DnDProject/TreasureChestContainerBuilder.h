#pragma once
#include "containerbuilder.h"
#include <Windows.h>

class TreasureChestContainerBuilder :
	public ContainerBuilder
{
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
	}

};

