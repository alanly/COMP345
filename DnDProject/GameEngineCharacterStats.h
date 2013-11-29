#pragma once

#include "GameObject.h"
#include "Character.h"
#include "LoaderParameters.h"

class GameEngineCharacterStats : public GameObject
{
	private:
		Character* character;
	public:
		GameEngineCharacterStats(LoaderParameters* parameters, Character* character);
		~GameEngineCharacterStats(void);
		
		void draw();
		void loadTextures();
		void handleMainEvents();
		void setCharacter(Character* character);
};

