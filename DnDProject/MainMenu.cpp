#include "MainMenu.h"
#include "TextureManager.h"
#include "ButtonConstants.h"
#include "Game.h"

MainMenu::MainMenu(LoaderParameters* parameters) : GameObject(parameters)
{
	playGameButton = new GameObject(new LoaderParameters(100, 400, 238, 36, 0, 0, "playGameButton"));
	mapEditorButton = new GameObject(new LoaderParameters(100, 437, 238, 36, 0, 0, "mapEditorButton"));
	quitButton = new GameObject(new LoaderParameters(100, 474, 238, 36, 0, 0, "quitButton"));

	loadTextures();
}

MainMenu::~MainMenu() { }

void MainMenu::draw()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "main_menu"), Game::getInstance()->getRenderer());
	playGameButton->draw();
	mapEditorButton->draw();
	quitButton->draw();
}

void MainMenu::handleEvents()
{
	playGameButton->handleEvents();
	mapEditorButton->handleEvents();
	quitButton->handleEvents();

	if (playGameButton->isClicked())
	{
		Game::getInstance()->setCurrentView(enumUtility::Character_Editor);
		playGameButton->resetClicked();
	} else if (mapEditorButton->isClicked())
	{
		Game::getInstance()->setCurrentView(enumUtility::Map_Editor);
		mapEditorButton->resetClicked();
	} else if (quitButton->isClicked())
	{
		Game::getInstance()->quit();
	}
}

void MainMenu::loadTextures()
{
	TextureManager::getInstance()->load("img/game/btn/btn_play.png", playGameButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_map_editor.png", mapEditorButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_quit.png", quitButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("img/game/ui/main_menu.png", "main_menu", Game::getInstance()->getRenderer());
}
