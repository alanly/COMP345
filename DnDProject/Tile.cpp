#include "Tile.h"

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
	if (this->type == STONEWALL ||
		this->type == WATER) {
		return false;
	} else {
		return true;
	}
}
