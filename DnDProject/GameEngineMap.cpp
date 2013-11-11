#include "GameEngineMap.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"

#include <iostream>


GameEngineMap::GameEngineMap(LoaderParameters* parameters, Map* map, Character* character) : GameObject(parameters)
{
	this->map = map;
	this->character = character;

	// Since the map view size depends on the cell size and how many cells there are, we set the parameters here.
	this->parameters->setWidth(map->getWidth() * CELL_SIZE);
	this->parameters->setHeight(map->getBreadth() * CELL_SIZE);

	loadTextures();
}

GameEngineMap::~GameEngineMap()
{
}

void GameEngineMap::drawTile(LoaderParameters* tile)
{
	TextureManager::getInstance()->draw(tile, Game::getInstance()->getRenderer());
}

int GameEngineMap::getMouseClickedRow()
{
	return (InputHandler::getInstance()->getMouseY() - parameters->getYPos()) / CELL_SIZE;
}

int GameEngineMap::getMouseClickedColumn()
{
	return (InputHandler::getInstance()->getMouseX() - parameters->getXPos()) / CELL_SIZE;
}

void GameEngineMap::draw()
{
	// 
	LoaderParameters* tile = nullptr;

	int startX = map->getCharacterPosition().x - 7;
	int startY = map->getCharacterPosition().y - 7;
	//cout<<"["<<map->getCharacterPosition().x<<", "<<map->getCharacterPosition().x<<"]"<<endl;
	//cout<<"drawing from: "<<startX<<", "<<startY<<" to "<<startX+15<<", "<<startY+15<<endl;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//cout<<(16 + (j * CELL_SIZE))<<" ";
			//tile = new LoaderParameters(16 + (j * CELL_SIZE), 16 + (i * CELL_SIZE), CELL_SIZE, CELL_SIZE, 0, 0, "emptyTile");
			tile = new LoaderParameters(16 + j*32 , 16 +i*32 , CELL_SIZE, CELL_SIZE, 0, 0, "emptyTile");

			if ((startX > -1 && startX < 15 && startY > -1 && startY < 15)) {
							drawTile(tile);
				if (map->getEndPosition().x == startX && map->getEndPosition().y == startY)
				{
					//tile = new LoaderParameters(16 + j * CELL_SIZE, 16 +  i * CELL_SIZE, CELL_SIZE, CELL_SIZE, 0, 0, "endTile");
					tile->setId("endTile");
					drawTile(tile);
				}
				if (map->getBeginPosition().x == startX && map->getBeginPosition().y == startY)
				{
					tile->setId("beginTile");
					drawTile(tile);
				}

				if (i == 7 && j == 7) {
					tile->setId("characterTile");
					drawTile(tile);
				}
			}
			startX++;
		}
		//cout<<startY<<endl;
		startY++;
		startX=map->getCharacterPosition().x - 7;
	}

	delete tile;
}

void GameEngineMap::loadTextures()
{
	TextureManager::getInstance()->load("images/map-view/empty-tile.png", "emptyTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/character-tile.png", "characterTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/opponent-tile.png", "opponentTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/chest-tile.png", "chestTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/wall-tile.png", "wallTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/begin-tile.png", "beginTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/end-tile.png", "endTile", Game::getInstance()->getRenderer());
}
