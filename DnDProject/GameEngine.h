#pragma once

#include "GameObject.h"
#include "GameEngineMap.h"
#include "Character.h"
#include "Map.h"
#include "GameEngineSideBar.h"
#include "GameEngineConsole.h"
#include "Console.h"

class GameEngine : public GameObject
{
private:
	enum GameEngineView {MAIN,
						GAMEOVER};

	bool drawFlag;
	int drawCount;

	GameObject* gameUI;
	GameObject* gameOver;
	Character* c;

	Map* map;
	GameEngineMap* mapView;
	GameEngineSideBar* sideBar;
	GameEngineView currentView;
	GameEngineConsole* console;

	bool allGone;

	GameObject* winScreen;

public:
	vector<Monster> monsters;

	GameEngine(LoaderParameters* parameters);
	~GameEngine();

	void drawMainView();

	void handleMainEvents();
	void handleEvents();
	void setCharacter(Character*);
	void draw();
	//void handleEvents();
	void loadTextures();
	void setMap(Map* map);
};

