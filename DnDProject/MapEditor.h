#pragma once

#include "GameObject.h"
#include "MapView.h"


class MapEditor : public GameObject
{
private:
	enum MapEditorView {ENTRY,
					EDITOR,
					MAP_SIZE,
					SAVE,
					LOAD};

	// Predefined map sizes.
	static const int SMALL_MAP_BREADTH = 7;
	static const int SMALL_MAP_WIDTH = 7;
	static const int MEDIUM_MAP_BREADTH = 8;
	static const int MEDIUM_MAP_WIDTH = 10;
	static const int LARGE_MAP_BREADTH = 11;
	static const int LARGE_MAP_WIDTH = 13;

	// This button lets you go back to the main menu.
	GameObject* mainMenuButton;

	// Entry view.
	GameObject* newMapButton;
	GameObject* loadMapButton;

	// Map size view.
	GameObject* smallMapButton;
	GameObject* mediumMapButton;
	GameObject* largeMapButton;

	// Editor view.
	Map* map;
	MapView* mapView;
	GameObject* validateMapButton;
	GameObject* validityLbl;
	GameObject* saveMapButton;

	// Load view.
	vector<GameObject*> saves;

	MapEditorView currentView;

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

