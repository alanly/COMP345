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
	d->constructCharacter("Player1",1);
	c = d->getCharacter();
	map = new Map(20, 20, Position(1, 1), Position(5, 1));
	mapView = new GameEngineMap(new LoaderParameters(16, 16,670, 480, 0, 0, "gameEngineMap"), map, c, 1);
	sideBar = new GameEngineSideBar(new LoaderParameters(720, 16, 0, 0, 0, 0, "gameEngineMap"),c);
	console = new GameEngineConsole(new LoaderParameters(24, 518, 400, 400, 0, 0, "gameEngineConsole"));
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
	console->draw();
}
void GameEngine::handleMainEvents()
{
	gameUI->handleEvents();
	mapView->handleEvents();

	if (gameUI->isClicked())
	{
		gameUI->resetClicked();

		//if (mapView->isClicked())
		//{
			mapView->resetClicked();

			Position click(mapView->getMouseClickedColumn(), mapView->getMouseClickedRow());

			string s = pathFind(map->getMap(), map->getCharacterPosition().x, map->getCharacterPosition().y, click.x, click.y);

			//cout<<s<<endl;

			while (s.length() != 0) {

				
				
			if (s.length() == 1)
			{
				vector<Monster> monsters = map->getMonsters();
				for (int i = 0; i < monsters.size(); i++)
				{
					Monster monster = monsters[i];

					if (click == monster.getPosition())
					{
						int initiative = Dice::roleTwentySideDice() + this->c->getAttackBonus();

						//if (initiative > monster.getArmorClass())
						//{
							int damageDone = (this->c->getStrength()) + (this->c->getAttackBonus());
							monster.setCurrentHitPoints((monster.getCurrentHitPoints()) - damageDone);
						//}
						
						int damageTaken = (monster.getStrength()) + (monster.getAttackBonus());
						this->c->setCurrentHitPoints((this->c->getCurrentHitPoints()) - damageTaken);
						//Console::getInstance()->addLine((string)this->c->getCurrentHitPoints());
						
						cout << "Character health: " << this->c->getCurrentHitPoints() << endl;
						cout << "Monster health: " << monster.getCurrentHitPoints() << endl;					}
				}
			}



				SDL_RenderClear(Game::getInstance()->getRenderer());

				map->moveCharacter((Direction)(s.front() - '0'));
				gameUI->draw();
				mapView->draw();
				console->draw();

				SDL_RenderPresent(Game::getInstance()->getRenderer());
				SDL_Delay(100);
				s = s.substr(1, s.length());
			}
			//map->moveCharacter(click);
		//}
	}
	string input = InputHandler::getInstance()->getInput();
	if (input != "") {
		char inputChar = input[0];
		//cout<< inputChar<<endl;
		if (mapView->getMode() == 0) {
			if (input == "W") {
								map->moveCharacter(UP);
			} else if (input == "A") {
								map->moveCharacter(LEFT);
			} else if (input == "S") {
								map->moveCharacter(DOWN);
			} else if (input == "D") {
						map->moveCharacter(RIGHT);
			}
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
	ArmourItem* ar = new ArmourItem("Item 1", "dec");
	character->addItemToInventory(ar);
	sideBar->setCharacter(character);
	mapView->setCharacter(character);
	this->c = character;
}
void GameEngine::setMap(Map* map){
	this->mapView->setMap(map);
	this->map = map;
}