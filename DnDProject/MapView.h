#pragma once

#include <vector>

#include "GameObject.h"
#include "Map.h"

using namespace std;

class MapView : public GameObject
{
private:
	/* Anything smaller than 50 will clip the tiles (note: you have to rebuild the project when you change
	this value). */
	static const int CELL_SIZE = 50;

	Map* map;

	void drawTile(LoaderParameters* tile);

public:
	MapView(LoaderParameters* parameters, Map* map);
	~MapView();

	// Returns the most recent row and column of the map that was clicked.
	int getMouseClickedRow();
	int getMouseClickedColumn();

	void draw();
	void loadTextures();
};

