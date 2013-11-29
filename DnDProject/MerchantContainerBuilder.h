#pragma once
#include "ContainerBuilder.h"

class MerchantContainerBuilder :
	public ContainerBuilder
{
public:

	MerchantContainerBuilder(void)
	{
	}

	~MerchantContainerBuilder(void)
	{
	}

	void buildContainer()
	{
		this->container = new Container(ContainerType::MERCHANT);
	}

};

