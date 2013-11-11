#include "MapView.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"


MapView::MapView(LoaderParameters* parameters, Map* map) : GameObject(parameters)
{
	this->map = map;

	// Since the map view size depends on the cell size and how many cells there are, we set the parameters here.
	this->parameters->setWidth(map->getWidth() * CELL_SIZE);
	this->parameters->setHeight(map->getBreadth() * CELL_SIZE);

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

	for (int i = 0; i < map->getBreadth(); i++)
	{
		for (int j = 0; j < map->getWidth(); j++)
		{
			tile = new LoaderParameters(parameters->getXPos() + (j * CELL_SIZE), parameters->getYPos() + (i * CELL_SIZE), CELL_SIZE, CELL_SIZE, 0, 0, "emptyTile");

			drawTile(tile);

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

			switch (map->getCellState(Position(j, i)))
			{
			case CHARACTER:
				tile->setId("characterTile");
				drawTile(tile);
				break;
			case CHEST:
				tile->setId("chestTile");
				drawTile(tile);
				break;
			case OPPONENT:
				tile->setId("opponentTile");
				drawTile(tile);
				break;
			case WALL:
				tile->setId("wallTile");
				drawTile(tile);
				break;
			}
		}
	}

	delete tile;
}

void MapView::loadTextures()
{
	TextureManager::getInstance()->load("images/map-view/empty-tile.png", "emptyTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/character-tile.png", "characterTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/opponent-tile.png", "opponentTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/chest-tile.png", "chestTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/wall-tile.png", "wallTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/begin-tile.png", "beginTile", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/map-view/end-tile.png", "endTile", Game::getInstance()->getRenderer());
}
