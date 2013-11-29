#pragma once
#include "Character.h"

class CharacterBuilder
{
	public:
	//Get the character
	Character* getCharacter(){ return c; }
    //build a generic empty Pizza
	void createNewCharacter(){ c = new Character("Player 1",1); }
    //Create the character
	virtual void buildDefaultCharacteristics(string name, int level) = 0;
	virtual void buildStats() = 0;

  protected:
    //Product built by Character Builder
    Character* c;
};

