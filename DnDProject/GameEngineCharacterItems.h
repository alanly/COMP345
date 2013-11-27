#pragma once
#include "GameObject.h"
#include "Character.h"
#include "LoaderParameters.h"

class GameEngineCharacterItems  : public GameObject
{
	private:
		Character* character;
	public:
		GameEngineCharacterItems(LoaderParameters* parameters, Character* character);
		~GameEngineCharacterItems(void);

		void draw();
		void loadTextures();


		void handleMainEvents();
};

