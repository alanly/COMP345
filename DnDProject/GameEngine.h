#pragma once

#include "GameObject.h"
#include "GameEngineMap.h"
#include "Character.h"
#include "Map.h"

class GameEngine : public GameObject
{
private:
	enum GameEngineView {MAIN,
						GAMEOVER};

	bool drawFlag;
	int drawCount;

	GameObject* gameUI;

	Character* c;

	Map* map;
	GameEngineMap* mapView;

	GameEngineView currentView;

public:
	GameEngine(LoaderParameters* parameters);
	~GameEngine();

	void drawMainView();

	void handleMainEvents();
	void handleEvents();

	void draw();
	//void handleEvents();
	void loadTextures();
};

