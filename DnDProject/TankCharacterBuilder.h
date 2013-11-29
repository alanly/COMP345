#pragma once
#include "CharacterBuilder.h"
#include "Character.h"

class TankCharacterBuilder : public CharacterBuilder
{
	public:
		TankCharacterBuilder(void);
		~TankCharacterBuilder(void);
		void buildDefaultCharacteristics(string name, int level);
		void buildStats(void);
};

