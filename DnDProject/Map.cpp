#include <iostream>
#include "Map.h"
#include "SDL.h"

Map::Map(int width, int height) : map(height, vector<Tile>(width))
{
	setCharacterPosition(Position(0, 0));

	createDefaultMap();
}

Map::Map(int width, int height, Position begin, Position end) : map(height, vector<Tile>(width))
{
	setBeginPosition(begin);
	setEndPosition(end);
	setCharacterPosition(begin);

	createDefaultMap();
}

/* remove when map loading and stuff works */
void Map::createDefaultMap() {
	for (int y = 0; y < getHeight(); y++)
		for (int x = 0; x < getWidth(); x++)
			this->map[x][y].setType(GRASS);
	
	this->map[1][3].setType(WATER);
	this->map[2][3].setType(STONEWALL);
	this->map[3][3].setType(STONEWALL);
}

Map::~Map(void) {}

int Map::getHeight() { return map.size(); }
int Map::getWidth() { return map[0].size(); }

void Map::setCharacterPosition(Position p) { this->characterPosition = p; }
void Map::setBeginPosition(Position p) { this->beginPosition = p; }
void Map::setEndPosition(Position p) { this->endPosition = p; }

Position Map::getCharacterPosition() { return characterPosition; }
Position Map::getBeginPosition() { return beginPosition; }
Position Map::getEndPosition() { return endPosition; }

/* Returns type of tile at Position p */
Type Map::getType(Position p)
{
	return this->map[p.x][p.y].getType();
}

void Map::setType(Position p, Type t)
{
	this->map[p.x][p.y].setType(t);
}

void Map::moveCharacter(Direction d)
{
	Position p = getCharacterPosition();

	switch (d)
	{
	case UP:
			p.y--;
		break;
	case RIGHT:
			p.x++;
		break;
	case DOWN:
			p.y++;
		break;
	case LEFT:
			p.x--;
		break;
	}

	// second check is probably bad practice
	if (isValidPosition(p) && this->map[p.x][p.y].isWalkable()) {
		setCharacterPosition(p);
	}
}

/* Move map (for editor mode) */
void Map::moveMap(Direction d)
{
	Position p = getCharacterPosition();

	switch (d)
	{
	case UP:
			p.y--;
		break;
	case RIGHT:
			p.x++;
		break;
	case DOWN:
			p.y++;
		break;
	case LEFT:
			p.x--;
		break;
	}

	if (isValidPosition(p)) {
		setCharacterPosition(p);
	}
}

/* Is position within map bounds? */
bool Map::isValidPosition(const Position& p)
{
	return ((p.x < (int)getWidth()) && (p.x > -1) && (p.y < (int)getHeight()) && (p.y > -1));
}

/* Get a pointer to this map object */
vector< vector<Tile> > Map::getMap() {
	return this->map;
}