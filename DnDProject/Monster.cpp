#include "Monster.h"


Monster::Monster(string name, int level, string desc, int exp) : Entity(name,level)
{
	this->description = desc;
	this->exp = exp;
}


Monster::~Monster(void)
{
}
int Monster::getExp()
{
	return this->exp;
}
