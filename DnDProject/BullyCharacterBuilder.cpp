#include "BullyCharacterBuilder.h"
#include "Dice.h"
#include <algorithm>
#include <iostream>
#include <functional>

BullyCharacterBuilder::BullyCharacterBuilder(void)
{
}


BullyCharacterBuilder::~BullyCharacterBuilder(void)
{
}

void BullyCharacterBuilder::buildDefaultCharacteristics(string name, int level)
{
	this->c->setName(name);
	this->c->setLevel(level);
}
void BullyCharacterBuilder::buildStats(void)
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
	characterStatistics[enumUtility::Strength] = stats[0];
	characterStatistics[enumUtility::Constitution] = stats[1];
	characterStatistics[enumUtility::Dexterity] = stats[2];
	characterStatistics[enumUtility::Inteligence] = stats[3];
	characterStatistics[enumUtility::Charisma] = stats[4];
	characterStatistics[enumUtility::Wisdom] = stats[5];

	this->c->setStatistics(characterStatistics);
}
