#include <iostream>

#include "MapEditor.h"
#include "TextureManager.h"
#include "ButtonConstants.h"
#include "dirent.h"
#include "Game.h"

MapEditor::MapEditor(LoaderParameters* parameters) : GameObject(parameters)
{
	int initialX, initialY;
	ButtonConstants::determineInitialButtonPositions(&initialX, &initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 3, 3, 2);

	newMapButton = new GameObject(new LoaderParameters(initialX, initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "newMapButton"));
	loadMapButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT + ButtonConstants::VERTICAL_SPACING, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "loadMapButton"));
	mainMenuButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT*2 + ButtonConstants::VERTICAL_SPACING*2, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "mainMenuButtonME"));

	ButtonConstants::determineInitialButtonPositions(&initialX, &initialY, ButtonConstants::SMALL_WIDTH, ButtonConstants::SMALL_HEIGHT, 4, 3, 2);

	smallMapButton = new GameObject(new LoaderParameters(initialX, initialY, ButtonConstants::SMALL_WIDTH, ButtonConstants::SMALL_HEIGHT, 0, 0, "smallMapButton"));
	mediumMapButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::SMALL_HEIGHT + ButtonConstants::VERTICAL_SPACING, ButtonConstants::SMALL_WIDTH, ButtonConstants::SMALL_HEIGHT, 0, 0, "mediumMapButton"));
	largeMapButton = new GameObject(new LoaderParameters(initialX, initialY + 2 * ButtonConstants::SMALL_HEIGHT + 2 * ButtonConstants::VERTICAL_SPACING, ButtonConstants::SMALL_WIDTH, ButtonConstants::SMALL_HEIGHT, 0, 0, "largeMapButton"));

	// Initialize the map editor view.
	currentView = MapEditorView::ENTRY;

	validityLbl = new GameObject(new LoaderParameters(700, 60, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "validLbl"));
	validateMapButton = new GameObject(new LoaderParameters(700, 60 + ButtonConstants::MEDIUM_HEIGHT + ButtonConstants::VERTICAL_SPACING, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "validateMapButton"));
	saveMapButton = new GameObject(new LoaderParameters(700, 60 + ButtonConstants::MEDIUM_HEIGHT*2 + ButtonConstants::VERTICAL_SPACING*2, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "saveMapButton"));

	loadTextures();
}


MapEditor::~MapEditor()
{
}

void MapEditor::drawEntryView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "mainMenuBg"), Game::getInstance()->getRenderer());

	newMapButton->draw();
	loadMapButton->draw();

	int initialX, initialY;
	ButtonConstants::determineInitialButtonPositions(&initialX, &initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 3, 3, 2);
	TextureManager::getInstance()->load("images/buttons/main_menu_medium.png", mainMenuButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	mainMenuButton->getParameters()->setXPos(initialX);
	mainMenuButton->getParameters()->setYPos(initialY + ButtonConstants::MEDIUM_HEIGHT * 2 + ButtonConstants::VERTICAL_SPACING * 2);
	mainMenuButton->getParameters()->setWidth(ButtonConstants::MEDIUM_WIDTH);
	mainMenuButton->getParameters()->setHeight(ButtonConstants::MEDIUM_HEIGHT);

	mainMenuButton->draw();
}

void MapEditor::drawEditorView()
{
	mapView->draw();
	validateMapButton->draw();
	validityLbl->draw();
	saveMapButton->draw();

	TextureManager::getInstance()->load("images/buttons/main_menu_medium.png", mainMenuButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	mainMenuButton->getParameters()->setXPos(700);
	mainMenuButton->getParameters()->setYPos(60 + ButtonConstants::MEDIUM_HEIGHT*3 + ButtonConstants::VERTICAL_SPACING*3);
	mainMenuButton->getParameters()->setWidth(ButtonConstants::MEDIUM_WIDTH);
	mainMenuButton->getParameters()->setHeight(ButtonConstants::MEDIUM_HEIGHT);

	mainMenuButton->draw();
}

void MapEditor::drawMapSizeView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "mainMenuBg"), Game::getInstance()->getRenderer());

	smallMapButton->draw();
	mediumMapButton->draw();
	largeMapButton->draw();

	int initialX, initialY;
	ButtonConstants::determineInitialButtonPositions(&initialX, &initialY, ButtonConstants::SMALL_WIDTH, ButtonConstants::SMALL_HEIGHT, 4, 3, 2);
	TextureManager::getInstance()->load("images/buttons/main_menu_small.png", mainMenuButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	mainMenuButton->getParameters()->setXPos(initialX);
	mainMenuButton->getParameters()->setYPos(initialY + ButtonConstants::SMALL_HEIGHT * 3 + ButtonConstants::VERTICAL_SPACING * 3);
	mainMenuButton->getParameters()->setWidth(ButtonConstants::SMALL_WIDTH);
	mainMenuButton->getParameters()->setHeight(ButtonConstants::SMALL_HEIGHT);

	mainMenuButton->draw();
}

void MapEditor::drawSaveView()
{

}

void MapEditor::drawLoadView()
{
	string curr_directory = "saves\\character\\";
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
	mapView->handleEvents();
	validateMapButton->handleEvents();
	saveMapButton->handleEvents();

	if (mapView->isClicked())
	{
		Position clickedPosition(mapView->getMouseClickedColumn(), mapView->getMouseClickedRow());

		CellState nextState;

		switch (map->getCellState(clickedPosition))
		{
		case CellState::EMPTY:
			if (clickedPosition == map->getEndPosition())
				nextState = CellState::CHARACTER;
			else
				nextState = CellState::WALL;
			break;
		case CellState::WALL:
			nextState = CellState::OPPONENT;
			break;
		case CellState:: CHARACTER:
			nextState = CellState::CHARACTER;
			break;
		case CellState::OPPONENT:
			nextState = CellState::CHEST;
			break;
		case CellState::CHEST:
			nextState = CellState::EMPTY;
			break;
		}

		if (nextState == CellState::CHARACTER)
		{
			map->setCharacterPosition(clickedPosition);
			map->setBeginPosition(clickedPosition);
		}
		else
		{
			if (nextState == CellState::EMPTY)
				map->setEndPosition(clickedPosition);
			map->setCellState(clickedPosition, nextState);
		}

		mapView->resetClicked();
	}
	if (validateMapButton->isClicked())
	{
		if (map->validate())
		{
			validityLbl->getParameters()->setId("validLbl");
		}
		else
		{
			validityLbl->getParameters()->setId("invalidLbl");
		}
		validateMapButton->resetClicked();
	}
	if (saveMapButton->isClicked())
	{
		// Saving the map woooooooooooooohoooooooooooo!!!
		saveMapButton->resetClicked();
	}
}

void MapEditor::handleMapSizeViewEvents()
{
	smallMapButton->handleEvents();
	mediumMapButton->handleEvents();
	largeMapButton->handleEvents();

	if (smallMapButton->isClicked())
	{
		map = new Map(SMALL_MAP_BREADTH, SMALL_MAP_WIDTH, Position(0, 0), Position(SMALL_MAP_WIDTH - 1, SMALL_MAP_BREADTH - 1));
		mapView = new MapView(new LoaderParameters(35, 65, 0, 0, 0, 0, "mapView"), map);
		currentView = MapEditorView::EDITOR;
		smallMapButton->resetClicked();
	}
	if (mediumMapButton->isClicked())
	{
		map = new Map(MEDIUM_MAP_BREADTH, MEDIUM_MAP_WIDTH, Position(0, 0), Position(MEDIUM_MAP_WIDTH - 1, MEDIUM_MAP_BREADTH - 1));
		mapView = new MapView(new LoaderParameters(35, 65, 0, 0, 0, 0, "mapView"), map);
		currentView = MapEditorView::EDITOR;
		mediumMapButton->resetClicked();
	}
	if (largeMapButton->isClicked())
	{
		map = new Map(LARGE_MAP_BREADTH, LARGE_MAP_WIDTH, Position(0, 0), Position(LARGE_MAP_WIDTH - 1, LARGE_MAP_BREADTH - 1));
		mapView = new MapView(new LoaderParameters(35, 65, 0, 0, 0, 0, "mapView"), map);
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
				cout << (*iter)->getParameters()->getId() << " will be loaded change view to game view with new character" << endl;
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
	TextureManager::getInstance()->load("images/buttons/main_menu_medium.png", mainMenuButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("images/buttons/create_a_map_medium.png", newMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/load_a_map_medium.png", loadMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("images/buttons/small_small.png", smallMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/medium_small.png", mediumMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/large_small.png", largeMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	
	TextureManager::getInstance()->load("images/buttons/validate_map_medium.png", validateMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/labels/valid_medium.png", "validLbl", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/labels/invalid_medium.png", "invalidLbl", Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("images/buttons/save_map_medium.png", saveMapButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("images/main-screen.png", "mainMenuBg", Game::getInstance()->getRenderer());
}
