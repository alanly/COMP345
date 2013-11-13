#include "GameEngineMap.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"

#include <iostream>


GameEngineMap::GameEngineMap(LoaderParameters* parameters, Map* map, Character* character) : GameObject(parameters)
{
	this->map = map;
	this->character = character;

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
	//return (InputHandler::getInstance()->getMouseY() - parameters->getYPos()) / CELL_SIZE;
	return (InputHandler::getInstance()->getMouseY() - parameters->getYPos()) / CELL_SIZE + 
		map->getCharacterPosition().y - 7;
}

int GameEngineMap::getMouseClickedColumn()
{
	return (InputHandler::getInstance()->getMouseX() - parameters->getXPos()) / CELL_SIZE + 
		map->getCharacterPosition().x - 10;
}

void GameEngineMap::draw()
{
	LoaderParameters* tile = nullptr;

	int startX = map->getCharacterPosition().x - 10;
	int startY = map->getCharacterPosition().y - 7;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			tile = new LoaderParameters(16 + j*32 , 16 + i*32 , CELL_SIZE, CELL_SIZE, 0, 0, "tile_empty");

			if ((startX > -1 && startX < map->getWidth() && startY > -1 && startY < map->getHeight())) {
				//drawTile(tile);

				switch (map->getType(Position(startX, startY)))
				{
				case EMPTY:
					tile->setId("tile_empty");
					drawTile(tile);
					break;
				case GRASS:
					tile->setId("tile_grass");
					drawTile(tile);
					break;
				case DARKGRASS:
					tile->setId("tile_darkgrass");
					drawTile(tile);
					break;
				case STONEWALL:
					tile->setId("tile_stonewall");
					drawTile(tile);
					break;
				}

				// start or end
				if (map->getEndPosition().x == startX && map->getEndPosition().y == startY)
				{
					tile->setId("misc_end");
					drawTile(tile);
				} else if (map->getBeginPosition().x == startX && map->getBeginPosition().y == startY)
				{
					tile->setId("misc_start");
					drawTile(tile);
				}

				// draw character
				if (i == 7 && j == 10) {
					tile->setId("char_default");
					drawTile(tile);
				}
			}
			startX++;
		}
		startY++;
		startX = map->getCharacterPosition().x - 10;
	}

	delete tile;
}

void GameEngineMap::loadTextures()
{
	// tiles
	TextureManager::getInstance()->load("img/game/tile/tile_empty.png", "tile_empty", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_grass.png", "tile_grass", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_stonewall.png", "tile_stonewall", Game::getInstance()->getRenderer());

	// misc
	TextureManager::getInstance()->load("img/game/misc/misc_start.png", "misc_start", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/misc/misc_end.png", "misc_end", Game::getInstance()->getRenderer());

	// chars
	TextureManager::getInstance()->load("img/game/char/char_default.png", "char_default", Game::getInstance()->getRenderer());
}
