#include "GameEngine.h"
#include "TextureManager.h"
#include <iostream>
#include "Game.h"
#include "InputHandler.h"

GameEngine::GameEngine(LoaderParameters* parameters) : GameObject(parameters)
{
	gameUI = new GameObject(new LoaderParameters(0, 0, 960, 640,  0, 0, "gameUI"));
	c = new Character("Player", 1);
	map = new Map(7, 10, Position(1, 1), Position(5, 1));
	mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "gameEngineMap"), map, c);
	currentView = GameEngineView::MAIN;

	loadTextures();
}

GameEngine::~GameEngine()
{
}

void GameEngine::drawMainView()
{
	gameUI->draw();
	mapView->draw();
}

void GameEngine::handleMainEvents()
{
	gameUI->handleEvents();

	if (gameUI->isClicked())
	{
		Position click(mapView->getMouseClickedColumn(), mapView->getMouseClickedRow());
		map->moveCharacter(click);
		gameUI->resetClicked();
	}
	string input = InputHandler::getInstance()->getInput();
	if (input != "") {
		char inputChar = input[0];

		if (input == "W") {
			//map->setCharacterPosition(Position(map->getCharacterPosition().x, (map->getCharacterPosition().y)-1));
			map->moveCharacter(UP);
		} else if (input == "A") {
			//map->setCharacterPosition(Position((map->getCharacterPosition().x)-1, map->getCharacterPosition().y));
			map->moveCharacter(LEFT);
		} else if (input == "S") {
			//map->setCharacterPosition(Position(map->getCharacterPosition().x, (map->getCharacterPosition().y)+1));
			map->moveCharacter(DOWN);
		} else if (input == "D") {
			//map->setCharacterPosition(Position((map->getCharacterPosition().x)+1, map->getCharacterPosition().y));
			map->moveCharacter(RIGHT);
		}
		//cout<<"["<<map->getCharacterPosition().x<<", "<<map->getCharacterPosition().y<<"]"<<endl;
	}
}

void GameEngine::handleEvents() {
	handleMainEvents();
}

void GameEngine::draw() {

	switch (currentView)
	{
	case GameEngineView::MAIN:
		drawMainView();
		break;
	}
	
}

void GameEngine::loadTextures() {
	TextureManager::getInstance()->load("img/game/ui/game_ui.png", gameUI->getParameters()->getId(), Game::getInstance()->getRenderer());
}
