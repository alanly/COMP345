#pragma once

#include <string>

using namespace std;

class LoaderParameters
{
private:
	// The position of the object's sprite relative to the window.
	int xPos;
	int yPos;

	// The dimensions of the object's sprite.
	int width;
	int height;

	// The row and column of a sprite in the spritesheet.
	int row;
	int column;

	// A unique identifier for the object (can be anything..)
	string id;

public:
	LoaderParameters() {};
	LoaderParameters(int xPos, int yPos, int width, int height, int row, int column, string id);
	
	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
	int getHeight() const;
	int getRow() const;
	int getColumn() const;

	string getId() const;

	void setXPos(int xPos);
	void setYPos(int yPos);
	void setWidth(int width);
	void setHeight(int height);
	void setRow(int row);
	void setColumn(int column);

	void setId(string id);
};

