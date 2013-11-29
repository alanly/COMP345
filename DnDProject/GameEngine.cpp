#pragma once
#include "GameEngine.h"
#include "TextureManager.h"
#include <iostream>
#include "Game.h"
#include "InputHandler.h"
#include "Director.h"
#include "TankCharacterBuilder.h"
#include "AStar.h"

GameEngine::GameEngine(LoaderParameters* parameters) : GameObject(parameters)
{
	gameUI = new GameObject(new LoaderParameters(0, 0, 960, 640,  0, 0, "gameUI"));
	Director* d = new Director();
	TankCharacterBuilder* tank = new TankCharacterBuilder();
	d->setCharacterBuilder(tank);
	d->constructCharacter("RMT",1);
	c = d->getCharacter();
	ArmourItem* item = new ArmourItem("Armor","Desc");
	c->addItemToInventory(item);
	HelmetItem* hel = new HelmetItem("Helmet1","Desc");
	c->addItemToInventory(hel);

	map = new Map(20, 20, Position(1, 1), Position(5, 1));
	mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "gameEngineMap"), map, c, 1);
	sideBar = new GameEngineSideBar(new LoaderParameters(720, 336, 0, 0, 0, 0, "gameEngineMap"),c);
	currentView = GameEngineView::MAIN;

	loadTextures();
}

GameEngine::~GameEngine()
{
}

void GameEngine::drawMainView()
{

	gameUI->draw();
	sideBar->draw();
	mapView->draw();
}

void GameEngine::handleMainEvents()
{
	gameUI->handleEvents();

	if (gameUI->isClicked())
	{
		Position click(mapView->getMouseClickedColumn(), mapView->getMouseClickedRow());
		gameUI->resetClicked();

		string s = pathFind(map->getMap(), map->getCharacterPosition().x, map->getCharacterPosition().y, click.x, click.y);

		//cout<<s<<endl;

		while (s.length() != 0) {
			SDL_RenderClear(Game::getInstance()->getRenderer());

			map->moveCharacter((Direction)(s.front() - '0'));
			gameUI->draw();
			mapView->draw();

			SDL_RenderPresent(Game::getInstance()->getRenderer());
			SDL_Delay(100);
			s = s.substr(1, s.length());
		}
		//map->moveCharacter(click);
	}
	string input = InputHandler::getInstance()->getInput();
	if (input != "") {
		char inputChar = input[0];
		//cout<< inputChar<<endl;
		if (mapView->getMode() == 0) {
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

void GameEngine::setCharacter(Character* character)
{
	sideBar->setCharacter(character);
	mapView->setCharacter(character);
	this->c = character;
}
void GameEngine::setMap(Map* map){
	this->mapView->setMap(map);
	this->map = map;
}