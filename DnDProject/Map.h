#pragma once

#include <ctime>
#include <vector>
#include "Container.h"
#include "Position.h"
#include "Tile.h"

using namespace std;

enum Direction {UP, RIGHT, DOWN, LEFT};

class Map
{
private:
	vector< vector<Tile> > map;
	vector< vector<Container> > chests;

	Position characterPosition;
	Position beginPosition;
	Position endPosition;

public:
	Map(int width, int height);
	Map(int width, int height, Position begin, Position end);
	~Map();

	int getHeight();
	int getWidth();

	Position getCharacterPosition();
	Position getBeginPosition();
	Position getEndPosition();

	Type getType(Position p);

	void setCharacterPosition(Position p);
	void setBeginPosition(Position p);
	void setEndPosition(Position p);

	void moveCharacter(Direction d);
	void moveCharacter(Position p);

	bool isValidPosition(const Position& p);

	void createDefaultMap();
};
