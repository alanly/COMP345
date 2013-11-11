#include <SDL.h>

#include "InputHandler.h"
#include "Game.h"
#include <iostream>
InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler()
{
	reset();
	keyButtonStates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT) // Left mouse button clicked.
	{
		mouseButtonStates[LEFT_BUTTON] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) // Right mouse button clicked.
	{
		mouseButtonStates[RIGHT_BUTTON] = true;
	}
	setMousePosition(event.motion.x, event.motion.y); // Record the position that was clicked.
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT) // Left mouse button released.
	{
		mouseButtonStates[LEFT_BUTTON] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT) // Right mouse button released.
	{
		mouseButtonStates[RIGHT_BUTTON] = false;
	}
}
void InputHandler::onKeyPress(SDL_Event& event)
{
	input = SDL_GetKeyName(event.key.keysym.sym);
}

void InputHandler::setMousePosition(int mouseX, int mouseY)
{
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

void InputHandler::update()
{
	SDL_Event event;

	// Handle the escape key and quit the program.
	if (getKeyButtonState(SDL_SCANCODE_ESCAPE))
		Game::getInstance()->quit();

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::getInstance()->quit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			onKeyPress(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::reset()
{
	mouseButtonStates.clear();

	// Initialize vector elements to false, meaning that nothing is clicked.
	for (int i = 0; i < 2; i++)
	{
		mouseButtonStates.push_back(false);
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return mouseButtonStates[buttonNumber];
}

bool InputHandler::getKeyButtonState(SDL_Scancode key)
{
	if(keyButtonStates != 0) // The length of the array is not zero.
	{
		if (keyButtonStates[key]) // We'll return a bool for convenience.
			return true;
		else
			return false;
	}
	return false;
}
string InputHandler::getInput()
{
	string temp = input;
	input = "";
	return temp;
}
int InputHandler::getMouseX()
{
	return mouseX;
}

int InputHandler::getMouseY()
{
	return mouseY;
}

InputHandler* InputHandler::getInstance()
{
	if (instance == nullptr)
	{
		instance = new InputHandler();
	}
	return instance;
}

void InputHandler::resetInstance()
{
	delete instance;
	instance = NULL;
}