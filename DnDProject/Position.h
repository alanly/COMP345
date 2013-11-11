#pragma once

// Defines a Position using x and y coordinates.
struct Position {
	int x;
	int y;

	Position(int x = 0, int y = 0) 
		: x(x), y(y) {}

	Position& operator=(const Position& position)
	{
		x = position.x;
		y = position.y;

		return *this;
	}

	bool operator==(const Position& position) const
	{
		return ((x == position.x) && (y == position.y));
	}
};