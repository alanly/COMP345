#pragma once

#include "GameObject.h"

class GameEngineConsole : public GameObject
{
private:
	GameObject* line1;
	GameObject* line2;	
	GameObject* line3;

public:
	GameEngineConsole(LoaderParameters* parameters);
	~GameEngineConsole(void);

	void draw();
	void handleEvents();
	void loadTextures();
};

