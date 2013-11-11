#pragma once

#include "GameObject.h"
#include "GameEngineMap.h"
#include "Character.h"
#include "Map.h"

class GameEngine : public GameObject
{
private:
	enum MapEditorView {MAIN,
						GAMEOVER};

	GameObject* gameUI;

	Character* c;

	// Editor view.
	Map* map;
	GameEngineMap* mapView;

	MapEditorView currentView;

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

