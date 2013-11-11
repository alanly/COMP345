#include <iostream>

#include "Map.h"

Map::Map(int breadth, int width) : map(breadth, vector<CellState>(width))
{

}

Map::Map(int breadth, int width, Position beginPosition, Position endPosition) : map(breadth, vector<CellState>(width))
{
	setBeginPosition(beginPosition);
	setEndPosition(endPosition);

	// The character always spawns at the beginning position.
	setCharacterPosition(beginPosition);
}

Map::~Map(void) {}

int Map::getBreadth()
{
	return map.size();
}

int Map::getWidth()
{
	return map[0].size();
}

CellState Map::getCellState(Position position)
{
	if (isValidPosition(position))
		return map[position.x][position.y];
	else
		cerr << "Error: Map.getCellState -> Invalid position\n";
	
	return WALL;
}

Position Map::getCharacterPosition()
{
	return characterPosition;
}

Position Map::getEndPosition()
{
	return endPosition;
}

Position Map::getBeginPosition()
{
	return beginPosition;
}

void Map::setCellState(Position position, CellState cellState)
{
	if (isValidPosition(position))
	{
		map[position.x][position.y] = cellState;
	}
	else
		cerr << "Error: Map.setCellState -> Invalid position\n";
}

void Map::setCharacterPosition(Position characterPosition)
{	
	//fix this
	if (isValidPosition(characterPosition)) {
		setCellState(this->characterPosition, EMPTY);
		setCellState(characterPosition, CHARACTER);
		this->characterPosition = characterPosition;
	}
	//cout<<this->characterPosition.x<<" "<<this->characterPosition.y;
}

void Map::setBeginPosition(Position beginPosition)
{
	if (isValidPosition(beginPosition))
	{
		setCharacterPosition(beginPosition);
		setCellState(beginPosition, CHARACTER);
		this->beginPosition = beginPosition;
	}
	else
		cerr << "Error: Map.setBeginPosition -> Invalid position\n";
}

void Map::setEndPosition(Position endPosition)
{
	if (isValidPosition(endPosition))
	{
		setCellState(endPosition, EMPTY);
		this->endPosition = endPosition;
	}
	else
		cerr << "Error: Map.setEndPosition -> Invalid position\n";
}

bool Map::validate()
{
	// Start the capture the time to make sure that the function doesn't crash the program with its recursive calls.
	functionStartTime = clock();

	if (beginPosition == endPosition)
		return false;
	else
		return checkForEnd(beginPosition); // Begin the recursive calls.
}

Position Map::movePosition(Position position, Direction direction)
{
	Position newPosition = position;

	switch (direction)
	{
	case UP:
			newPosition.y--;
		break;
	case RIGHT:
			newPosition.x++;
		break;
	case DOWN:
			newPosition.y++;
		break;
	case LEFT:
			newPosition.x--;
		break;
	}

	if (isValidPosition(newPosition))
		return newPosition;

	return position;
}

bool Map::isValidPosition(const Position& position)
{
	return ((position.y < (int)map.size()) && (position.y >= 0 ) && (position.x < (int)map[0].size()) && (position.x >= 0));
}

bool Map::checkForEnd(Position currentPosition)
{
	// Check to see if 2 seconds have passed. If is has, we concur that the map is invalid.
	if (((clock() - functionStartTime) / (double) CLOCKS_PER_SEC) > HANG_TIME_ALLOWANCE)
		return false;

	bool isFound = false; // Did we reach the end position.
	CellState currentCellState = getCellState(currentPosition);

	// We have reached the end. This is the base case for the recursive calls.
	if (currentPosition == endPosition)
		return true;

	/* If the current cell is empty or a character, we set it to a wall so
	that we know that the cell has been visited. */
	if ((currentCellState == EMPTY) || (currentCellState == CHARACTER) || (currentCellState == OPPONENT))
	{
		setCellState(currentPosition, WALL);

		/* Check every possible path. This is necessary because we cannot prove that
		the map is invalid until we have done so. */
		if (checkForEnd(movePosition(currentPosition, UP)) ||
			checkForEnd(movePosition(currentPosition, RIGHT)) ||
			checkForEnd(movePosition(currentPosition, DOWN)) ||
			checkForEnd(movePosition(currentPosition, LEFT)))
			isFound = true; // We have reached the end.

		/* Put the cell back to its original state. If this isn't done, the entire map
		would be a wall. */
		setCellState(currentPosition, currentCellState);
	}
	return isFound;
}