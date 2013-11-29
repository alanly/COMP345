#pragma once
#include "CharacterBuilder.h"

class NimbleCharacterBuilder : public CharacterBuilder
{
	public:
		NimbleCharacterBuilder(void);
		~NimbleCharacterBuilder(void);
		void buildDefaultCharacteristics(string name, int level);
		void buildStats(void);
};

