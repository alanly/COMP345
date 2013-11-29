#include "TankCharacterBuilder.h"
#include "Dice.h"
#include <algorithm>
#include <iostream>
#include <functional>
TankCharacterBuilder::TankCharacterBuilder(void)
{
}


TankCharacterBuilder::~TankCharacterBuilder(void)
{
}

void TankCharacterBuilder::buildDefaultCharacteristics(string name, int level)
{
	this->c->setName(name);
	this->c->setLevel(level);
	this->c->setClassification(enumUtility::Tank);
}
void TankCharacterBuilder::buildStats(void)
{
	int stats[6];
	for(int i = enumUtility::Strength; i != enumUtility::Wisdom+1; i++)
	{
		int rolls[] = {Dice::roleSixSideDice(),Dice::roleSixSideDice(),Dice::roleSixSideDice(),Dice::roleSixSideDice()};
		std::sort(std::begin(rolls), std::end(rolls), std::greater<int>());
		int total = 0;
		for(int j = 0; j< 3; j++)
		{
			total += rolls[j];
		}

		stats[i] = total;
	}
	std::sort(std::begin(stats), std::end(stats), std::greater<int>());
	map<enumUtility::abilityModifer,int> characterStatistics;
	characterStatistics[enumUtility::Constitution] = stats[0];
	characterStatistics[enumUtility::Dexterity] = stats[1];
	characterStatistics[enumUtility::Strength] = stats[2];
	characterStatistics[enumUtility::Inteligence] = stats[3];
	characterStatistics[enumUtility::Charisma] = stats[4];
	characterStatistics[enumUtility::Wisdom] = stats[5];
	this->c->setStatistics(characterStatistics);
}