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
		map<GameObject*, Item*> items;
	public:
		GameEngineCharacterItems(LoaderParameters* parameters, Character* character);
		~GameEngineCharacterItems(void);

		void draw();
		void loadTextures();

		void setCharacter(Character* character);
		void handleMainEvents();
};

