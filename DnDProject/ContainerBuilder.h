#pragma once
#include "Container.h"
#include "ContainerType.h"

class ContainerBuilder
{
protected:
	ContainerType type;
	Container* container;

public:
	virtual void buildContainer() =0;

	Container* getContainer() {
		return this->container;
	}
};

