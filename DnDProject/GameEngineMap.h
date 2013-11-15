#pragma once

#include <vector>

#include "GameObject.h"
#include "Map.h"
#include "Character.h"

using namespace std;

class GameEngineMap : public GameObject
{
private:
	static const int CELL_SIZE = 32;

	int mode;

	Map* map;
	Character* character;

	void drawTile(LoaderParameters* tile);

public:
	GameEngineMap(LoaderParameters* parameters, Map* map, Character* character, int mode);
	~GameEngineMap();

	// Returns the most recent row and column of the map that was clicked.
	int getMouseClickedRow();
	int getMouseClickedColumn();

	void draw();
	void loadTextures();

	int getMode();

	void handleMainEvents();

};

