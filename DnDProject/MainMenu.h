#pragma once

#include "GameObject.h"

class MainMenu : public GameObject
{
private:
	GameObject* playGameButton;
	GameObject* mapEditorButton;
	GameObject* quitButton;

	void determineEntryViewButtonPositions(int*, int*);

public:
	MainMenu(LoaderParameters* parameters);
	~MainMenu();

	void draw();
	void handleEvents();
	void loadTextures();
};

