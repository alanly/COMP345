#pragma once

#include <SDL.h>
#include <string>
#include <map>

#include "GameObject.h"
#include "Enum_Utility.h"

using namespace std;

class Game
{
private:
	Game() {};
	~Game();

	// This is a singleton class.
	static Game* instance;

	SDL_Window* window;
	SDL_Renderer* renderer;

	// A flag to determine if the game is running.
	bool running;
	enumUtility::gameView currentView;
	/* This map contains pointers to all of the views in the game
	that can be rendered. */
	map<enumUtility::gameView, GameObject*> gameObjects;

	int _WINDOW_WIDTH;
	int _WINDOW_HEIGHT;

public:
	// Initializes the game window to the given properties.
	bool init(const char* title, int xPos, int yPos, int width, int height, int flags);
	
	// Creates the game's objects and adds to the gameObject vector.
	void initGameObjects();

	// Renders all of the game objects.
	void render();

	
	// Captures and handles events.
	void handleEvents();

	// Clean up SDL.
	void clean();

	// Ends the application.
	void quit();

	bool isRunning();


	SDL_Renderer* getRenderer() const;

	// Singleton function.
	static Game* getInstance();

	void setCurrentView(enumUtility::gameView);

	int getWindowWidth() { return this->_WINDOW_WIDTH; };
	int getWindowHeight() { return this->_WINDOW_HEIGHT; };
};

