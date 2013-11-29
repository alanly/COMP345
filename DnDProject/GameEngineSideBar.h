#pragma once

#include <vector>

#include "GameObject.h"
#include "Map.h"
#include "Character.h"
#include "GameEngineCharacterItems.h"
#include "GameEngineCharacterStats.h"

using namespace std;

class GameEngineSideBar : public GameObject
{
private:
	Character* character;
	GameEngineCharacterItems* charItemView;
	GameEngineCharacterStats* charStatsView;
public:
	GameEngineSideBar(LoaderParameters* parameters, Character* character);
	~GameEngineSideBar();

	void draw();
	void loadTextures();


	void handleMainEvents();
	void setCharacter(Character* character);
};

