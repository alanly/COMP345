#pragma once
#include "CharacterBuilder.h";

class BullyCharacterBuilder: public CharacterBuilder
{
	public:
		BullyCharacterBuilder();
		~BullyCharacterBuilder();
		void buildDefaultCharacteristics(string name, int level);
		void buildStats(void);
};