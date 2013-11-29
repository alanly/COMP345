#pragma once
#include "CharacterBuilder.h"
class Director
{
	private:
		CharacterBuilder* charBuilder;
	public:
		void setCharacterBuilder(CharacterBuilder* builder);
		Character* getCharacter();
		void constructCharacter(string name, int level);
};

