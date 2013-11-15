#include "Tile.h"
#include <iostream>

using namespace std;
Tile::Tile(void)
{
	this->type = EMPTY;
}

Tile::Tile(Type t)
{
	this->type = t;
}

Tile::~Tile(void)
{
}

Type Tile::getType()
{
	return this->type;
}

void Tile::setType(Type t)
{
	this->type = t;
}

bool Tile::isWalkable()
{
	if (getType() == STONEWALL ||
		getType() == WATER) {
		return false;
	} else {
		return true;
	}
}
