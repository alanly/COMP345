#pragma once

#include <ctime>
#include <vector>
#include "Container.h"
#include "Position.h"
#include "Tile.h"
#include "Monster.h"

#include "tinyxml2.h"

using namespace std;

enum Direction {RIGHT, DOWN, LEFT, UP};

class Map
{
private:
	vector< vector<Tile> > map;
	vector<Monster> monsters;

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
	void setType(Position p, Type t);

	vector< vector<Tile> > getMap();

	void setCharacterPosition(Position p);
	void setBeginPosition(Position p);
	void setEndPosition(Position p);

	void moveCharacter(Direction d);

	bool isValidPosition(const Position& p);

	void createDefaultMap();

	void moveMap(Direction d);

	void spawnMonster(Monster m);

	vector<Monster> getMonsters();

	bool isMonsterAround(const Position& p);
	bool isMonster(const Position& p);

	// load save functions
	void saveToFile(string fn);
	static Map* readFromFile(string filename);

	void damageMonster(int m, int hp);
	void killMonster(int m);
};
