#include "GameEngineConsole.h"
#include "TextureManager.h"
#include "Game.h"
#include "Console.h"

GameEngineConsole::GameEngineConsole(LoaderParameters* parameters) : GameObject(parameters)
{
	line1 = new GameObject(new LoaderParameters(parameters->getXPos(), parameters->getYPos(), 480, 30, 0, 0, "consoleL1"));
	line2 = new GameObject(new LoaderParameters(parameters->getXPos(), parameters->getYPos() + 30, 480, 30, 0, 0, "consoleL2"));
	line3 = new GameObject(new LoaderParameters(parameters->getXPos(), parameters->getYPos() + 60, 480, 30, 0, 0, "consoleL3"));

	loadTextures();
}


GameEngineConsole::~GameEngineConsole(void)
{
}

void GameEngineConsole::draw()
{
	loadTextures();
	line1->draw();
	line2->draw();
	line3->draw();
}

void GameEngineConsole::handleEvents()
{

}

void GameEngineConsole::loadTextures()
{
	TextureManager::getInstance()->loadFont(line1->getParameters()->getId(),Game::getInstance()->getRenderer(), Console::getInstance()->getLine(1));
	TextureManager::getInstance()->loadFont(line2->getParameters()->getId(),Game::getInstance()->getRenderer(), Console::getInstance()->getLine(2));
	TextureManager::getInstance()->loadFont(line3->getParameters()->getId(),Game::getInstance()->getRenderer(), Console::getInstance()->getLine(3));
}
