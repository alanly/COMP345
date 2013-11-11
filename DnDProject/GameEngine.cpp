#include "GameEngine.h"
#include "TextureManager.h"
#include <iostream>
#include "Game.h"
#include "InputHandler.h"

GameEngine::GameEngine(LoaderParameters* parameters) : GameObject(parameters)
{
	gameUI = new GameObject(new LoaderParameters(0, 0, 960, 640,  0, 0, "gameUI"));

	c = new Character("Player", 1);

	map = new Map(15, 15, Position(5, 5), Position(5, 7));
	mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "gameEngineMap"), map, c);

	currentView = MapEditorView::MAIN;

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
		//currentView = MapEditorView::MAP_SIZE;
		gameUI->resetClicked();
	}
	string input = InputHandler::getInstance()->getInput();
	//cout<<input<<endl;
	if (input != "") {
		char inputChar = input[0];

		if (input == "W") {
			map->setCharacterPosition(Position(map->getCharacterPosition().x, (map->getCharacterPosition().y)-1));
		} else if (input == "A") {
			map->setCharacterPosition(Position((map->getCharacterPosition().x)-1, map->getCharacterPosition().y));
		} else if (input == "S") {
			map->setCharacterPosition(Position(map->getCharacterPosition().x, (map->getCharacterPosition().y)+1));
		} else if (input == "D") {
			map->setCharacterPosition(Position((map->getCharacterPosition().x)+1, map->getCharacterPosition().y));
		}
		//cout<<"["<<c->getPosition().x<<", "<<c->getPosition().y<<"]";
		cout<<"["<<map->getCharacterPosition().x<<", "<<map->getCharacterPosition().y<<"]"<<endl;
	}
	//cout<<"before"<<map->getCharacterPosition().x<<endl;
	
	//cout<<"after"<<map->getCharacterPosition().x<<endl;
}

void GameEngine::handleEvents() {
	handleMainEvents();
}

void GameEngine::draw() {

	switch (currentView)
	{
	case MapEditorView::MAIN:
		drawMainView();
		break;
	}
	
}

void GameEngine::loadTextures() {
	TextureManager::getInstance()->load("images/map-view/game_ui.png", gameUI->getParameters()->getId(), Game::getInstance()->getRenderer());
}
