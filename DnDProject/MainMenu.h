#pragma once

#include "GameObject.h"

class MainMenu : public GameObject
{
private:
	//GameObject* newGameButton;
	//GameObject* continueButton;
	GameObject* playGameButton;
	GameObject* mapEditorButton;
	//GameObject* characterEditorButton;
	GameObject* quitButton;

	void determineEntryViewButtonPositions(int*, int*);

public:
	MainMenu(LoaderParameters* parameters);
	~MainMenu();

	void draw();
	void handleEvents();
	void loadTextures();
};

