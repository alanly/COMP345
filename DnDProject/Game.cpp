#include <SDL_image.h>
#include <iostream>

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenu.h"
#include "CharacterEditor.h"
#include "MapEditor.h"
#include "GameEngine.h"

using namespace std;

Game* Game::instance = 0;

Game::~Game()
{
	gameObjects.clear();
}

bool Game::init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL_Init: success\n";

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		this->_WINDOW_WIDTH = width;
		this->_WINDOW_HEIGHT = height;

		if (window != 0)
		{
			cout << "SDL_CreateWindow: success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0)
			{
				cout << "SDL_CreateRenderer: success\n";
				//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				
				initGameObjects();
			}
			else
			{
				cout << "SDL_CreateRenderer: fail\n";
				return false;
			}
		}
		else
		{
			cout << "SDL_CreateWindow: fail\n";
			return false;
		}
	}
	else
	{
		cout << "SDL_Init: fail\n";
		return false;
	}

	running = true;

	return true;
}

void Game::initGameObjects()
{
	// Here you would load all of the game objects and add them to the gameObjects vector
	gameObjects[enumUtility::Main_Menu] = new MainMenu(new LoaderParameters(0, 0, 600, 600, 0, 0, "mainMenu"));
	gameObjects[enumUtility::Character_Editor] = new CharacterEditor(new LoaderParameters(0, 0, 600, 600, 0, 0, "characterEditor"));
	gameObjects[enumUtility::Map_Editor] = new MapEditor(new LoaderParameters(0, 0, 600, 600, 0, 0, "mapEditor"));
	gameObjects[enumUtility::Game_Main] = new GameEngine(new LoaderParameters(0, 0, 600, 600, 0, 0, "gameEngine"));
}

void Game::render()
{
	SDL_RenderClear(renderer);
	switch(currentView){
		case enumUtility::Main_Menu:
			// If the view is main menu, then we display it.
			((MainMenu*)gameObjects[enumUtility::Main_Menu])->draw();
			break;
		case enumUtility::Character_Editor:
			// If the view is main menu, then we display it.
			((CharacterEditor*)gameObjects[enumUtility::Character_Editor])->draw();
			break;
		case enumUtility::Map_Editor:
			// If the current view is the map editor, then we display it.
			((MapEditor*)gameObjects[enumUtility::Map_Editor])->draw();
			break;
		case enumUtility::Game_Main:
			// If the current view is the map editor, then we display it.
			((GameEngine*)gameObjects[enumUtility::Game_Main])->draw();
			break;
	}
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	InputHandler::getInstance()->update();

	switch(currentView){
		case enumUtility::Main_Menu:
			// If the current view is the main menu, then we update it / handle events.
			((MainMenu*)gameObjects[enumUtility::Main_Menu])->handleEvents();
			break;
		case enumUtility::Character_Editor:
			// If the current view is the main menu, then we update it / handle events.
			((CharacterEditor*)gameObjects[enumUtility::Character_Editor])->handleEvents();
			break;
		case enumUtility::Map_Editor:
			// If the current view is the map editor, then we display it.
			((MapEditor*)gameObjects[enumUtility::Map_Editor])->handleEvents();
			break;
		case enumUtility::Game_Main:
			// If the current view is the map editor, then we display it.
			((GameEngine*)gameObjects[enumUtility::Game_Main])->handleEvents();
			break;
	}

	InputHandler::getInstance()->reset();
}

void Game::clean()
{
	cout << "Cleaning the game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

void Game::quit()
{
	running = false;
}

bool Game::isRunning()
{
	return running;
}

SDL_Renderer* Game::getRenderer() const
{
	return renderer;
}

Game* Game::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Game();
	}
	return instance;
}
void Game::setCurrentView(enumUtility::gameView currentView)
{
	this->currentView = currentView;
}