#pragma once
#include "ContainerBuilder.h"

class ContainerBuildDirector
{
private:
	ContainerBuilder* builder;
public:

	ContainerBuildDirector(void)
	{
	}

	~ContainerBuildDirector(void)
	{
	}

	void setContainerBuilder(ContainerBuilder* builder)
	{
		this->builder = builder;
	}

	void buildContainer(void)
	{
		this->builder->buildContainer();
	}

};

