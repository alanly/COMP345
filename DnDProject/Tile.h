#pragma once

enum Type {EMPTY, GRASS, DARKGRASS, STONEWALL, WATER};

class Tile
{
private:
	Type type;

public:
	Tile(void);
	Tile(Type t);
	~Tile(void);

	Type getType();
	void setType(Type t);

	bool isWalkable();
};

