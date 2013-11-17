#pragma once

#include <iostream>

#include "MapEditor.h"
#include "TextureManager.h"
#include "ButtonConstants.h"
#include "dirent.h"
#include "Game.h"
#include "InputHandler.h"
//#include "AStar.h"

MapEditor::MapEditor(LoaderParameters* parameters) : GameObject(parameters)
{
	currentView = MapEditorView::ENTRY;
	currentTile = EMPTY;
	editorUI = new GameObject(new LoaderParameters(0, 0, 960, 640,  0, 0, "editorUI"));

	newMapButton = new GameObject(new LoaderParameters(150, 400, 238, 36, 0, 0, "newMapButton"));
	loadMapButton = new GameObject(new LoaderParameters(150, 450, 238, 36, 0, 0, "loadMapButton"));
	mainMenuButton = new GameObject(new LoaderParameters(150, 500, 238, 36, 0, 0, "mainMenuButton"));

	smallMapButton = new GameObject(new LoaderParameters(150, 350, 238, 36, 0, 0, "smallMapButton"));
	mediumMapButton = new GameObject(new LoaderParameters(150, 400, 238, 36, 0, 0, "mediumMapButton"));
	largeMapButton = new GameObject(new LoaderParameters(150, 450, 238, 36, 0, 0, "largeMapButton"));

	saveMapButton = new GameObject(new LoaderParameters(705, 536, 238, 36, 0, 0, "saveMapButton"));

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
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "createMapUI"), Game::getInstance()->getRenderer());

	newMapButton->draw();
	loadMapButton->draw();

	mainMenuButton->getParameters()->setXPos(150);
	mainMenuButton->getParameters()->setYPos(500);
	mainMenuButton->draw();
}

void MapEditor::drawMapSizeView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "createMapUI"), Game::getInstance()->getRenderer());

	smallMapButton->draw();
	mediumMapButton->draw();
	largeMapButton->draw();

	mainMenuButton->getParameters()->setXPos(150);
	mainMenuButton->getParameters()->setYPos(500);
	mainMenuButton->draw();
}

void MapEditor::drawEditorView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "gameUI"), Game::getInstance()->getRenderer());

	mapView->draw();
	saveMapButton->draw();

	mainMenuButton->getParameters()->setXPos(705);
	mainMenuButton->getParameters()->setYPos(586);
	mainMenuButton->draw();

	// draw tiles in the right pane
	tileEmptyButton->draw();
	tileGrassButton->draw();
	tileDarkGrassButton->draw();
	tileStoneWallButton->draw();
	tileWaterButton->draw();
}

void MapEditor::drawSaveView()
{}

void MapEditor::drawLoadView()
{
	string curr_directory = "sav\\map\\";
	string extension = "xml";
	if(saves.empty()){
		int currentX = 100;
		int currentY = 100;
		int increment = 35;
		DIR* dir_point = opendir(curr_directory.c_str());
        dirent* entry = readdir(dir_point);
        while (entry){                       // if !entry then end of directory
               if (entry->d_type == DT_REG){                // if entry is a regular file
                   std::string fname = entry->d_name;        // filename
                                                                                                // if filename's last characters are extension
                   if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos){
					   saves.push_back(new GameObject(new LoaderParameters(currentX,currentY,150,25,0,0,fname)));             // add filename to results vector
					   currentY += increment;
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
	newMapButton->handleEvents();
	loadMapButton->handleEvents();

	if (newMapButton->isClicked())
	{
		currentView = MapEditorView::MAP_SIZE;
		newMapButton->resetClicked();
	}
	if (loadMapButton->isClicked())
	{
		currentView = MapEditorView::LOAD;
		loadMapButton->resetClicked();
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

	editorUI->handleEvents();
	if (editorUI->isClicked())
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

	saveMapButton->handleEvents();
	if (saveMapButton->isClicked())
	{
		map->saveToFile("testmap.xml");
		saveMapButton->resetClicked();
	}

	editorUI->resetClicked();
}

void MapEditor::handleMapSizeViewEvents()
{
	smallMapButton->handleEvents();
	mediumMapButton->handleEvents();
	largeMapButton->handleEvents();

	if (smallMapButton->isClicked())
	{
		character = new Character("MAPEDIT", 1);
		map = new Map(10, 10, Position(0, 0), Position(5, 5));
		mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
		currentView = MapEditorView::EDITOR;
		smallMapButton->resetClicked();
	}
	if (mediumMapButton->isClicked())
	{
		character = new Character("MAPEDIT", 1);
		map = new Map(30, 30, Position(0, 0), Position(30 - 1, 30 - 1));
		mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
		currentView = MapEditorView::EDITOR;
		mediumMapButton->resetClicked();
	}
	if (largeMapButton->isClicked())
	{
		character = new Character("MAPEDIT", 1);
		map = new Map(100, 100, Position(0, 0), Position(100 - 1, 100 - 1));
		mapView = new GameEngineMap(new LoaderParameters(16, 16, 0, 0, 0, 0, "mapView"), map, character, 0);
		currentView = MapEditorView::EDITOR;
		largeMapButton->resetClicked();
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
	mainMenuButton->draw();

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
	// Handle if the main menu button was clicked.
	mainMenuButton->handleEvents();

	if (mainMenuButton->isClicked())
	{
		Game::getInstance()->setCurrentView(enumUtility::gameView::Main_Menu);
		currentView = MapEditorView::ENTRY;
		mainMenuButton->resetClicked();
	}
	else {
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
	TextureManager::getInstance()->load("img/game/btn/btn_main_menu.png", mainMenuButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/btn/btn_new_map.png", newMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_load_map.png", loadMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/btn/btn_small_map.png", smallMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_medium_map.png", mediumMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_large_map.png", largeMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	
	TextureManager::getInstance()->load("img/game/btn/btn_save_map.png", saveMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/ui/create_map.png", "createMapUI", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/ui/game_ui.png", "gameUI", Game::getInstance()->getRenderer());

	// this is duplicated from GameEngineMap.cpp, probably make a method for this somewhere
	// this is needed for the tiles view on the side
	TextureManager::getInstance()->load("img/game/tile/tile_empty.png", "tileEmptyButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_grass.png", "tileGrassButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_darkgrass.png", "tileDarkGrassButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_stonewall.png", "tileStoneWallButton", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/tile/tile_water.png", "tileWaterButton", Game::getInstance()->getRenderer());

}