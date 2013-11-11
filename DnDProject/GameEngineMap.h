#pragma once

#include <vector>

#include "GameObject.h"
#include "Map.h"
#include "Character.h"

using namespace std;

class GameEngineMap : public GameObject
{
private:
	/* Anything smaller than 20 will clip the tiles (note: you have to rebuild the project when you change
	this value). */
	static const int CELL_SIZE = 32;

	Map* map;
	Character* character;

	void drawTile(LoaderParameters* tile);

public:
	GameEngineMap(LoaderParameters* parameters, Map* map, Character* character);
	~GameEngineMap();

	// Returns the most recent row and column of the map that was clicked.
	int getMouseClickedRow();
	int getMouseClickedColumn();

	void draw();
	void loadTextures();
};

