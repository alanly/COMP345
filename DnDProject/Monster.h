#pragma once
#include "Entity.h"
#include <string>

class Monster : public Entity
{
	private: 
		string description;
		int exp;
	public:
		Monster(string,int, string, int);
		~Monster(void);

		int getExp();
};

