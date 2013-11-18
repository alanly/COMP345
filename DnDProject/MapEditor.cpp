//#include <iostream>
#include "MapEditor.h"
#include "TextureManager.h"
#include "dirent.h"
#include "Game.h"
#include "InputHandler.h"
//#include "AStar.h"

MapEditor::MapEditor(LoaderParameters* parameters) : GameObject(parameters)
{
	currentView = MapEditorView::ENTRY;
	currentTile = EMPTY;

	UI_Editor = new GameObject(new LoaderParameters(0, 0, 960, 640,  0, 0, "UI_Editor"));

	Button_Map_New = new GameObject(new LoaderParameters(80, 200, 180, 50, 0, 0, "Button_Map_New"));
	Button_Map_Load = new GameObject(new LoaderParameters(100, 250, 190, 48, 0, 0, "Button_Map_Load"));
	Button_Back = new GameObject(new LoaderParameters(0, 0, 96, 38, 0, 0, "Button_Back"));

	Button_Map_Small = new GameObject(new LoaderParameters(80, 200, 104, 38, 0, 0, "Button_Map_Small"));
	Button_Map_Medium = new GameObject(new LoaderParameters(100, 250, 144, 36, 0, 0, "Button_Map_Medium"));
	Button_Map_Large = new GameObject(new LoaderParameters(120, 300, 104, 52, 0, 0, "Button_Map_Large"));

	Button_Save_Map = new GameObject(new LoaderParameters(705, 536, 238, 36, 0, 0, "Button_Save_Map"));
	Button_Main_Menu = new GameObject(new LoaderParameters(705, 573, 238, 36, 0, 0, "Button_Main_Menu"));

	tileEmptyButton = new GameObject(new LoaderParameters(705, 17, 32, 32, 0, 0, "tileEmptyButton"));
	tileGrassButton = new GameObject(new LoaderParameters(738, 17, 32, 32, 0, 0, "tileGrassButton"));
	tileDarkGrassButton = new GameObject(new LoaderParameters(771, 17, 32, 32, 0, 0, "tileDarkGrassButton"));
	tileStoneWallButton = new GameObject(new LoaderParameters(804, 17, 32, 32, 0, 0, "tileStoneWallButton"));
	tileWaterButton = new GameObject(new LoaderParameters(837, 17, 32, 32, 0, 0, "tileWaterButton"));

	loadTextures();
}


MapEditor::~MapEditor()
{
}

void MapEditor::drawEntryView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Create_Map"), Game::getInstance()->getRenderer());

	Button_Map_New->draw();
	Button_Map_Load->draw();

	Button_Back->getParameters()->setXPos(120);
	Button_Back->getParameters()->setYPos(300);
	Button_Back->draw();
}

void MapEditor::drawMapSizeView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Create_Map"), Game::getInstance()->getRenderer());

	Button_Map_Small->draw();
	Button_Map_Medium->draw();
	Button_Map_Large->draw();

	Button_Back->getParameters()->setXPos(140);
	Button_Back->getParameters()->setYPos(350);
	Button_Back->draw();
}

void MapEditor::drawEditorView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Editor"), Game::getInstance()->getRenderer());

	mapView->draw();
	Button_Save_Map->draw();

	//Button_Back->getParameters()->setXPos(705);
	//Button_Back->getParameters()->setYPos(586);
	Button_Main_Menu->draw();

	// draw tiles in the right pane
	tileEmptyButton->draw();
	tileGrassButton->draw();
	tileDarkGrassButton->draw();
	tileStoneWallButton->draw();
	tileWaterButton->draw();
}

void MapEditor::drawSaveView()
{
}

void MapEditor::drawLoadView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Load_Map"), Game::getInstance()->getRenderer());

	Button_Back->getParameters()->setXPos(210);
	Button_Back->getParameters()->setYPos(450);
	Button_Back->draw();

	string curr_directory = "sav\\map\\";
	string extension = "xml";

	if(saves.empty()){
		int currentX = 60;
		int currentY = 200;
		int incrementX = 10;
		int incrementY = 35;
		DIR* dir_point = opendir(curr_directory.c_str());
        dirent* entry = readdir(dir_point);
        while (entry) { // if !entry then end of directory
               if (entry->d_type == DT_REG) { // if entry is a regular file
                   std::string fname = entry->d_name; // filename
                   // if filename's last characters are extension
                   if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos){
					   saves.push_back(new GameObject(new LoaderParameters(currentX, currentY, 300, 25, 0, 0, fname.substr(0, fname.length()-4))));
					   currentY += incrementY;
					   currentX += incrementX;
				   }
                }
                entry = readdir(dir_point);
        }
        loadSaveFiles();
	}
	drawSaveFiles();
}

void MapEditor::loadSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            TextureManager::getInstance()->loadFont((*iter)->getParameters()->getId(),Game::getInstance()->getRenderer(), (*iter)->getParameters()->getId());
        }
    }
}

void MapEditor::drawSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->draw();
        }
    }
}

void MapEditor::handleEntryViewEvents()
{
	Button_Map_New->handleEvents();
	Button_Map_Load->handleEvents();

	if (Button_Map_New->isClicked())
	{
		currentView = MapEditorView::MAP_SIZE;
		Button_Map_New->resetClicked();
	}
	if (Button_Map_Load->isClicked())
	{
		currentView = MapEditorView::LOAD;
		Button_Map_Load->resetClicked();
	}
}

void MapEditor::handleEditorViewEvents()
{
	string input = InputHandler::getInstance()->getInput();
	if (input != "") {
		if (input == "W" || input == "Up") {
			map->moveMap(UP);
		} else if (input == "A" || input == "Left") {
			map->moveMap(LEFT);
		} else if (input == "S" || input == "Down") {
			map->moveMap(DOWN);
		} else if (input == "D" || input == "Right") {
			map->moveMap(RIGHT);
		}
	}

	UI_Editor->handleEvents();
	if (UI_Editor->isClicked())
	{
		Position click(mapView->getMouseClickedColumn(), mapView->getMouseClickedRow());
		//currentTile = EMPTY;

		tileEmptyButton->handleEvents();
		tileGrassButton->handleEvents();
		tileDarkGrassButton->handleEvents();
		tileStoneWallButton->handleEvents();
		tileWaterButton->handleEvents();

		if (tileEmptyButton->isClicked()) {
			currentTile = EMPTY;
			tileEmptyButton->resetClicked();
		}
		if (tileGrassButton->isClicked()) {
			currentTile = GRASS;
			tileGrassButton->resetClicked();
		}
		if (tileDarkGrassButton->isClicked()) {
			currentTile = DARKGRASS;
			tileDarkGrassButton->resetClicked();
		}
		if (tileStoneWallButton->isClicked()) {
			currentTile = STONEWALL;
			tileStoneWallButton->resetClicked();
		}
		if (tileWaterButton->isClicked()) {
			currentTile = WATER;
			tileWaterButton->resetClicked();
		} 

		if (click.x > -1 && click.x < map->getWidth() && click.y > -1 && click.y < map->getHeight()) {
			map->setType(click, currentTile);
		}
	}

	Button_Save_Map->handleEvents();
	if (Button_Save_Map->isClicked())
	{
		map->saveToFile("testmap.xml");
		Button_Save_Map->resetClicked();
	}

	Button_Main_Menu->handleEvents();
	if (Button_Main_Menu->isClicked())
	{
		Game::getInstance()->setCurrentView(enumUtility::gameView::Main_Menu);
		currentView = MapEditorView::ENTRY;
		Button_Main_Menu->resetClicked();
	}

	UI_Editor->resetClicked();
}

void MapEditor::handleMapSizeViewEvents()
{
	Button_Map_Small->handleEvents();
	Button_Map_Medium->handleEvents();
	Button_Map_Large->handleEvents();

	if (Button_Map_Small->isClicked())
	{
		character = new Character("MAPEDIT", 1);
		map = new Map(10, 10, Position(0, 0), Position(5, 5));
		mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
		currentView = MapEditorView::EDITOR;
		Button_Map_Small->resetClicked();
	}
	if (Button_Map_Medium->isClicked())
	{
		character = new Character("MAPEDIT", 1);
		map = new Map(30, 30, Position(0, 0), Position(30 - 1, 30 - 1));
		mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
		currentView = MapEditorView::EDITOR;
		Button_Map_Medium->resetClicked();
	}
	if (Button_Map_Large->isClicked())
	{
		character = new Character("MAPEDIT", 1);
		map = new Map(100, 100, Position(0, 0), Position(100 - 1, 100 - 1));
		mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
		currentView = MapEditorView::EDITOR;
		Button_Map_Large->resetClicked();
	}
}

void MapEditor::handleLoadViewEvents()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->handleEvents();
			if((*iter)->isClicked())
			{
				(*iter)->resetClicked();
				//cout << (*iter)->getParameters()->getId() << " will be loaded change view to game view with new character" << endl;
				
				character = new Character("MAPEDIT", 1);
				map = map->readFromFile("testmap.xml");
				mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
				currentView = MapEditorView::EDITOR;
			}
        }
    }
}

void MapEditor::draw() {
	Button_Back->draw();

	switch (currentView)
	{
	case MapEditorView::ENTRY:
		drawEntryView();
		break;
	case MapEditorView::MAP_SIZE:
		drawMapSizeView();
		break;
	case MapEditorView::EDITOR:
		drawEditorView();
		break;
	case MapEditor::LOAD:
		drawLoadView();
		break;
	}
}

void MapEditor::handleEvents() {
	Button_Back->handleEvents();

	if (Button_Back->isClicked())
	{
		switch (currentView)
		{
		case MapEditorView::ENTRY:
			Game::getInstance()->setCurrentView(enumUtility::gameView::Main_Menu);
			currentView = MapEditorView::ENTRY;
			break;
		case MapEditorView::MAP_SIZE:
			currentView = MapEditorView::ENTRY;
			break;
		case MapEditorView::EDITOR:
			Game::getInstance()->setCurrentView(enumUtility::gameView::Main_Menu);
			currentView = MapEditorView::ENTRY;
			break;
		case MapEditor::LOAD:
			currentView = MapEditorView::ENTRY;
			break;
		}
		Button_Back->resetClicked();
	}
	else
	{
		switch (currentView)
		{
		case MapEditorView::ENTRY:
			handleEntryViewEvents();
			break;
		case MapEditorView::MAP_SIZE:
			handleMapSizeViewEvents();
			break;
		case MapEditorView::EDITOR:
			handleEditorViewEvents();
			break;
		case MapEditorView::LOAD:
			handleLoadViewEvents();
			break;
		}
	}
}

void MapEditor::loadTextures() {
	TextureManager::getInstance()->load("img/game/btn/btn_back.png", Button_Back->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/btn/btn_map_new.png", Button_Map_New->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_map_load.png", Button_Map_Load->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/btn/btn_map_small.png", Button_Map_Small->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_map_medium.png", Button_Map_Medium->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_map_large.png", Button_Map_Large->getParameters()->getId(), Game::getInstance()->getRenderer());
	
	TextureManager::getInstance()->load("img/game/btn/btn_save_map.png", Button_Save_Map->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_main_menu.png", Button_Main_Menu->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/ui/map_create.png", "UI_Create_Map", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/ui/map_load.png", "UI_Load_Map", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/ui/game_ui.png", "UI_Editor", Game::getInstance()->getRenderer());

	// this is duplicated from GameEngineMap.cpp, probably make a method for this somewhere
	// this is needed for the tiles view on the side
	TextureManager::getInstance()->load("img/game/tile/tile_empty.png", "tileEmptyButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_grass.png", "tileGrassButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_darkgrass.png", "tileDarkGrassButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_stonewall.png", "tileStoneWallButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_water.png", "tileWaterButton", Game::getInstance()->getRenderer());

}