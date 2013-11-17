#pragma once
#include "Entity.h"
#include "Position.h"
#include <string>

class Monster : public Entity
{
	private: 
		string description;
		int exp;
		Position pos;
	public:
		Monster(string,int, string, int, Position);
		~Monster(void);

		int getExp();

		// should move this to entity probably
		void setPosition(Position);
		Position getPosition();
};

