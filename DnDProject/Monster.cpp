#include "Monster.h"


Monster::Monster(string name, int level, string desc, int exp, Position p) : Entity(name,level)
{
	this->description = desc;
	this->exp = exp;
	this->pos = p;
}


Monster::~Monster(void)
{
}
int Monster::getExp()
{
	return this->exp;
}

void Monster::setPosition(Position p) {
	this->pos = p;
}

Position Monster::getPosition() {
	return this->pos;
}
int Monster::getArmorClass(){
	return 10 + getDexterity();
}
