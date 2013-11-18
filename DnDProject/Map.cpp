#include <fstream>
#include <iostream>
#include <string>
#include "Map.h"
#include "SDL.h"

Map::Map(int width, int height) : map(height, vector<Tile>(width))
{
	setCharacterPosition(Position(0, 0));

	createDefaultMap();
}

Map::Map(int width, int height, Position begin, Position end) : map(height, vector<Tile>(width))
{
	setBeginPosition(begin);
	setEndPosition(end);
	setCharacterPosition(begin);

	createDefaultMap();
}

/* remove when map loading and stuff works */
void Map::createDefaultMap() {
	for (int y = 0; y < getHeight(); y++)
		for (int x = 0; x < getWidth(); x++)
			this->map[x][y].setType(GRASS);
	
	this->map[1][3].setType(WATER);
	this->map[2][3].setType(STONEWALL);
	this->map[3][3].setType(STONEWALL);

	spawnMonster(Monster("Negro Demon", 1, "Big Black Demon", 666, Position(5, 5)));

}

vector<Monster> Map::getMonsters() {
	return this->monsters;
}

void Map::spawnMonster(Monster m)
{
	this->monsters.push_back(m);
}

Map::~Map(void) {}

int Map::getHeight() { return map.size(); }
int Map::getWidth() { return map[0].size(); }

void Map::setCharacterPosition(Position p) { this->characterPosition = p; }
void Map::setBeginPosition(Position p) { this->beginPosition = p; }
void Map::setEndPosition(Position p) { this->endPosition = p; }

Position Map::getCharacterPosition() { return characterPosition; }
Position Map::getBeginPosition() { return beginPosition; }
Position Map::getEndPosition() { return endPosition; }

/* Returns type of tile at Position p */
Type Map::getType(Position p)
{
	return this->map[p.x][p.y].getType();
}

void Map::setType(Position p, Type t)
{
	this->map[p.x][p.y].setType(t);
}

void Map::moveCharacter(Direction d)
{
	Position p = getCharacterPosition();

	switch (d)
	{
	case UP:
			p.y--;
		break;
	case RIGHT:
			p.x++;
		break;
	case DOWN:
			p.y++;
		break;
	case LEFT:
			p.x--;
		break;
	}

	// second check is probably bad practice
	if (isValidPosition(p) && this->map[p.x][p.y].isWalkable()) {
		setCharacterPosition(p);
	}
}

/* Move map (for editor mode) */
void Map::moveMap(Direction d)
{
	Position p = getCharacterPosition();

	switch (d)
	{
	case UP:
			p.y--;
		break;
	case RIGHT:
			p.x++;
		break;
	case DOWN:
			p.y++;
		break;
	case LEFT:
			p.x--;
		break;
	}

	if (isValidPosition(p)) {
		setCharacterPosition(p);
	}
}

/* Is position within map bounds? */
bool Map::isValidPosition(const Position& p)
{
	return ((p.x < (int)getWidth()) && (p.x > -1) && (p.y < (int)getHeight()) && (p.y > -1));
}

/* Get a pointer to this map object */
vector< vector<Tile> > Map::getMap() {
	return this->map;
}


void Map::saveToFile(string fn)
{
	using namespace tinyxml2;

	vector< vector<Tile> > map = this->map;
	Position charPosition = this->characterPosition;
	Position bPosition = this->beginPosition;
	Position ePosition = this->endPosition;

	int x, y;

	Type tile;

	XMLDocument doc;
	XMLNode* mapNode =  doc.NewElement("Map");
	XMLNode* tileNode;
	XMLText* tileType;

	string convert;

	const char* c;

	// Character Position
	XMLNode* positionNode = doc.NewElement("CharacterPosition");
	x = charPosition.x;
	y = charPosition.y;
	convert = to_string(x);
	c = convert.c_str();
	XMLNode* xPosition = doc.NewElement("x");
	XMLText* xText = doc.NewText(c);
	XMLNode* yPosition = doc.NewElement("y");
	XMLText* yText = doc.NewText(c);
	xPosition->InsertEndChild(xText);
	yPosition->InsertEndChild(yText);
	positionNode->InsertEndChild(xPosition);
	positionNode->InsertEndChild(yPosition);
	doc.InsertEndChild(positionNode);

	// Begin Position
	positionNode = doc.NewElement("BeginPosition");
	x = bPosition.x;
	y = bPosition.y;
	convert = to_string(x);
	c = convert.c_str();
	xPosition = doc.NewElement("x");
	xText = doc.NewText(c);
	yPosition = doc.NewElement("y");
	yText = doc.NewText(c);
	xPosition->InsertEndChild(xText);
	yPosition->InsertEndChild(yText);
	positionNode->InsertEndChild(xPosition);
	positionNode->InsertEndChild(yPosition);
	doc.InsertEndChild(positionNode);

	// End Position
	positionNode = doc.NewElement("EndPosition");
	x = ePosition.x;
	y = ePosition.y;
	convert = to_string(x);
	c = convert.c_str();
	xPosition = doc.NewElement("x");
	xText = doc.NewText(c);
	yPosition = doc.NewElement("y");
	yText = doc.NewText(c);
	xPosition->InsertEndChild(xText);
	yPosition->InsertEndChild(yText);
	positionNode->InsertEndChild(xPosition);
	positionNode->InsertEndChild(yPosition);
	doc.InsertEndChild(positionNode);

	// Tile info
	for (int col = 0; col < map.size(); col++)
	{
		for (int row = 0; row < map[col].size(); row++)
		{
			tileNode = doc.NewElement("Tile");

			tile = map.at(col).at(row).getType();

			convert = to_string(tile);
			c = convert.c_str();

			tileType = doc.NewText(c);
			tileNode->InsertEndChild(tileType);

			mapNode->InsertEndChild(tileNode);
		}
	}

	doc.InsertEndChild(mapNode);

	fn = "sav\\map\\" + fn;

	const char* f = fn.c_str();
	doc.SaveFile(f);
	cout<<"Saved map to file "<<f;
}

Map* Map::readFromFile(string filename)
{
	using namespace tinyxml2;

	filename = "sav\\map\\" + filename;
	const char* f = filename.c_str();

	XMLDocument doc;
	doc.LoadFile(f);

	int numberOfTiles = 0;

	string line;
	ifstream myfile(filename,ifstream::in);

	while (getline(myfile,line))
	{
		numberOfTiles++;
	}

	numberOfTiles = numberOfTiles - 17; // Accounts for tags that are not tiles

	int n = static_cast<int>(sqrt(numberOfTiles)); // n x n map

	int x,y;

	Type tileType;

	XMLElement* tileNode;

	// Character Position
	XMLElement* topChildLevel = doc.FirstChildElement("CharacterPosition");
	XMLElement* xPositionNode = topChildLevel->FirstChildElement("x");
	XMLElement* yPositionNode = topChildLevel->FirstChildElement("y");
	x = stoi(xPositionNode->GetText());
	y = stoi(yPositionNode->GetText());
	Position charPosition(x,y);

	// Begin Position
	topChildLevel = topChildLevel->NextSiblingElement();
	xPositionNode = topChildLevel->FirstChildElement("x");
	yPositionNode = topChildLevel->FirstChildElement("y");
	x = stoi(xPositionNode->GetText());
	y = stoi(yPositionNode->GetText());
	Position bPosition(x,y);

	//End Position
	topChildLevel = topChildLevel->NextSiblingElement();
	xPositionNode = topChildLevel->FirstChildElement("x");
	yPositionNode = topChildLevel->FirstChildElement("y");
	x = stoi(xPositionNode->GetText());
	y = stoi(yPositionNode->GetText());

	Position ePosition(x,y);
	Map* map = new Map(n, n, bPosition, ePosition);
	map->setCharacterPosition(charPosition);
	topChildLevel = topChildLevel->NextSiblingElement();
	tileNode = topChildLevel->FirstChildElement("Tile");

	for (int col = 0; col < n; col++)
	{
		for (int row = 0; row < n; row++)
		{
			Position currentCell(col,row);
			tileType = static_cast<Type>(stoi(tileNode->GetText()));
			map->setType(currentCell, tileType);
			tileNode = tileNode->NextSiblingElement();
		}
	}

	return map;
}