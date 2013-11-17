#pragma once

#include "GameObject.h"
#include "GameEngineMap.h"
#include "Character.h"

class MapEditor : public GameObject
{
private:
	enum MapEditorView {ENTRY,
					MAP_SIZE,
					EDITOR,
					SAVE,
					LOAD};

	GameObject* mainMenuButton;

	// Entry view
	GameObject* newMapButton;
	GameObject* loadMapButton;

	// Map size view
	GameObject* smallMapButton;
	GameObject* mediumMapButton;
	GameObject* largeMapButton;

	// Editor view
	Map* map;
	GameEngineMap* mapView;
	GameObject* saveMapButton;

	// Load view
	vector<GameObject*> saves;

	MapEditorView currentView;

	// tile buttons
	GameObject* tileEmptyButton;
	GameObject* tileGrassButton;
	GameObject* tileDarkGrassButton;
	GameObject* tileStoneWallButton;
	GameObject* tileWaterButton;

	Character* character; // dummy char for map movement

	GameObject* editorUI;

	Type currentTile;

public:
	MapEditor(LoaderParameters* parameters);
	~MapEditor();

	// These are functions used for the load map view.
	void loadSaveFiles();
	void drawSaveFiles();

	void drawEntryView();
	void drawEditorView();
	void drawMapSizeView();
	void drawSaveView();
	void drawLoadView();

	void handleEntryViewEvents();
	void handleEditorViewEvents();
	void handleMapSizeViewEvents();
	void handleLoadViewEvents();

	void draw();
	void handleEvents();
	void loadTextures();
};

