#pragma once
#include "GameObject.h"
#include "Character.h"
#include "LoaderParameters.h"
#include "TextureManager.h"
#include "Game.h"

class GameEngineCharacterItems  : public GameObject
{
	private:
		Character* character;
		vector<GameObject*> items;
	public:
		GameEngineCharacterItems(LoaderParameters* parameters, Character* character);
		~GameEngineCharacterItems(void);

		void draw();
		void loadTextures();


		void handleMainEvents();
};

