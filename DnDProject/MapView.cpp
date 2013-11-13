#include "MapView.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"


MapView::MapView(LoaderParameters* parameters, Map* map) : GameObject(parameters)
{
	this->map = map;

	// Since the map view size depends on the cell size and how many cells there are, we set the parameters here.
	this->parameters->setWidth(map->getWidth() * CELL_SIZE);
	this->parameters->setHeight(map->getHeight() * CELL_SIZE);

	loadTextures();
}

MapView::~MapView()
{
}

void MapView::drawTile(LoaderParameters* tile)
{
	TextureManager::getInstance()->draw(tile, Game::getInstance()->getRenderer());
}

int MapView::getMouseClickedRow()
{
	return (InputHandler::getInstance()->getMouseY() - parameters->getYPos()) / CELL_SIZE;
}

int MapView::getMouseClickedColumn()
{
	return (InputHandler::getInstance()->getMouseX() - parameters->getXPos()) / CELL_SIZE;
}

void MapView::draw()
{
	LoaderParameters* tile = nullptr;

	for (int i = 0; i < map->getHeight(); i++)
	{
		for (int j = 0; j < map->getWidth(); j++)
		{
			tile = new LoaderParameters(parameters->getXPos() + (j * CELL_SIZE), parameters->getYPos() + (i * CELL_SIZE), CELL_SIZE, CELL_SIZE, 0, 0, "emptyTile");

			drawTile(tile);

			/*
			if (map->getEndPosition().x == j && map->getEndPosition().y == i)
			{
				tile->setId("endTile");
				drawTile(tile);
			}
			if (map->getBeginPosition().x == j && map->getBeginPosition().y == i)
			{
				tile->setId("beginTile");
				drawTile(tile);
			}
			*/

			switch (map->getType(Position(j, i)))
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
		}
	}

	delete tile;
}

void MapView::loadTextures()
{
	TextureManager::getInstance()->load("img/game/tile/tile_empty.png", "tile_empty", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_grass.png", "tile_grass", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_darkgrass.png", "tile_darkgrass", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_stonewall.png", "tile_stonewall", Game::getInstance()->getRenderer());
}
