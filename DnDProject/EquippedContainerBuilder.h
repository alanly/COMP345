#pragma once
#include "containerbuilder.h"
class EquippedContainerBuilder :
	public ContainerBuilder
{
public:

	EquippedContainerBuilder(void)
	{
	}

	~EquippedContainerBuilder(void)
	{
	}

	void buildContainer()
	{
		this->container = new Container(ContainerType::EQUIPPED);
	}
};

