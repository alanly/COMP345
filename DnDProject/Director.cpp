#include "Director.h"


void Director::setCharacterBuilder(CharacterBuilder* builder)
{
	this->charBuilder = builder;
}
Character* Director::getCharacter()
{
	return charBuilder->getCharacter();
}

void Director::constructCharacter(string name, int level)
{
	charBuilder->createNewCharacter();
	charBuilder->buildDefaultCharacteristics(name, level);
	charBuilder->buildStats();
}