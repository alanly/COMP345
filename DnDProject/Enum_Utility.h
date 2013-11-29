#pragma once
#include "string.h"

namespace enumUtility
{

	//Enum type to classify the items
	enum equipmentType { Helmet, Armor, Boots, Belt, Weapon, Shield, Ring1, Ring2, Empty };
	enum characterClassifiction { Nimble, Tank, Bully, Monster };
	enum abilityModifer { Strength, Dexterity, Inteligence, Charisma, Constitution,Wisdom };
	enum gameView{ Main_Menu, Character_Editor, Map_Editor, Game_Main, Map_Chooser};
}