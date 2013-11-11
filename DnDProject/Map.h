#pragma once

#include <vector>
#include <ctime>

#include "Position.h"

using namespace std;

// Directions in which a move can be made on a map.
enum Direction {UP, RIGHT, DOWN, LEFT};

/* Each cell on the map can contain any one of these states. The
EMPTY state is the only state that a character can move through. */
enum CellState {EMPTY,
				WALL,
				CHARACTER,
				OPPONENT,
				CHEST};

class Map
{
private:
	vector< vector<CellState> > map;

	// The current position of the character. There is only one character on the map.
	Position characterPosition;

	// The begin position is where the character first spawns on the map.
	Position beginPosition;

	// If the character is at the end position, he/she has completed the map.
	Position endPosition;

	// This variable is used to make sure that the program doesn't crash when validating the map if it takes too long.
	clock_t functionStartTime;
	static const int HANG_TIME_ALLOWANCE = 2;

	// A function to be used recursively to validate a map.
	bool checkForEnd(Position position);

public:
	// The breadth and width are the dimensions of the map.
	Map(int breadth, int width);
	Map(int breadth, int width, Position beginPosition, Position endPosition);
	~Map();

	// Returns the dimensions of the map.
	int getBreadth();
	int getWidth();

	CellState getCellState(Position position);
	Position getCharacterPosition();
	Position getBeginPosition();
	Position getEndPosition();

	void setCellState(Position position, CellState cellState);
	void setCharacterPosition(Position characterPosition);
	void setBeginPosition(Position beginPosition);
	void setEndPosition(Position endPosition);

	/* Determines whether there is a clear path from the beginning position
	to the ending position on the map. */
	bool validate();

	/* Will move the given position in the direction specified
	and return the new position. It will not change the given position if
	the resulting position would be outside the bounds of the map.*/
	Position movePosition(Position position, Direction direction);

	// Checks to see whether the given position is within the map bounds.
	bool isValidPosition(const Position& position);	
};
