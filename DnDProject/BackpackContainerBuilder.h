#pragma once
#include "containerbuilder.h"

class BackpackContainerBuilder :
	public ContainerBuilder
{
public:
	BackpackContainerBuilder(void) {};
	~BackpackContainerBuilder(void) {};
	void buildContainer() {
		this->container = new Container(ContainerType::BACKPACK);
	};
};

