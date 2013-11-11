#pragma once

#include "LoaderParameters.h"

class GameObject
{
protected:
	// The object's onsceen properties.
	LoaderParameters* parameters;
	// This is true is the object has been clicked.
	bool clicked;

public:
	GameObject(LoaderParameters* parameters);

	LoaderParameters* getParameters();

	// Renders the object to the screen.
	void draw();

	// Handles user input.
	void handleEvents();

	bool isClicked();
	// Sets clicked to false.
	void resetClicked();

	void clean();
};

