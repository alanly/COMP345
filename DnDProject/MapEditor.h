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

	GameObject* Button_Back;

	GameObject* Button_Map_New;
	GameObject* Button_Map_Load;

	GameObject* Button_Map_Small;
	GameObject* Button_Map_Medium;
	GameObject* Button_Map_Large;

	GameObject* Button_Save_Map;
	GameObject* Button_Main_Menu;

	Map* map;
	GameEngineMap* mapView;

	vector<GameObject*> saves;

	MapEditorView currentView;

	GameObject* tileEmptyButton;
	GameObject* tileGrassButton;
	GameObject* tileDarkGrassButton;
	GameObject* tileStoneWallButton;
	GameObject* tileWaterButton;

	Character* character; // dummy char for map movement

	GameObject* UI_Editor;

	Type currentTile;

public:
	MapEditor(LoaderParameters* parameters);
	~MapEditor();

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

