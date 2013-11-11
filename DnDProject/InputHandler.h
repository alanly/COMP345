#pragma once

#include <SDL.h>
#include <vector>
#include <string.h>
using namespace std;

enum MouseButtons
{
	LEFT_BUTTON = 0,
	RIGHT_BUTTON = 1
};

class InputHandler
{
private:
	InputHandler();
	// This is a singleton class.
	static InputHandler* instance;
	string input;
	/* Each element contains true or false based on whether a mouse button is clicked or not respectively.
	Ex: mouseButtonStates[LEFT] returns true if the left mouse button is clicked. */
	vector<bool> mouseButtonStates;

	/* This is a pointer to an array of keyButtonStates that can be accessed using SDL Scancodes.
	Ex: keyButtonStates[SDL_SCANCODE_A] returns true if the 'a' key is pressed. */
	const Uint8* keyButtonStates;

	// The position of the last mouse click.
	int mouseX;
	int mouseY;

	// Some general mouse event handlers.
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onKeyPress(SDL_Event& event);
	// Will set the mouse's most recent position.
	void setMousePosition(int mouseX, int mouseY);

public:
	void update();

	// Resets all of the events that happened.
	void reset();

	// Returns true or false based on whether a mouse button is clicked or not respectively.
	bool getMouseButtonState(int buttonNumber);

	// Returns true or false based on whether a key button was clicked or not respectively.
	bool getKeyButtonState(SDL_Scancode key);

	// Returns the position of the most recent mouse click.
	int getMouseX();
	int getMouseY();
	string getInput();
	// Singleton function.
	static InputHandler* getInstance();

	// Destroy instance.
	static void resetInstance();
};
