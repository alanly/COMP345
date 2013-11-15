#include "MainMenu.h"
#include "TextureManager.h"
#include "ButtonConstants.h"
#include "Game.h"

void MainMenu::determineEntryViewButtonPositions(int *initialX, int *initialY)
{
	// Determine the layout of buttons for the entry view
	*initialX = (Game::getInstance()->getWindowWidth() / 2) - (ButtonConstants::MEDIUM_WIDTH / 2);
	*initialY = (Game::getInstance()->getWindowHeight() / 2)
		+ (Game::getInstance()->getWindowHeight() / 2)/2
		- (ButtonConstants::MEDIUM_HEIGHT * 3 + ButtonConstants::VERTICAL_SPACING*2)/2;
}

MainMenu::MainMenu(LoaderParameters* parameters) : GameObject(parameters)
{
	// Determine the layout of buttons.
	int initialX = 0;
	int initialY = 0;
	determineEntryViewButtonPositions(&initialX, &initialY);

	playGameButton = new GameObject(new LoaderParameters(initialX, initialY, 238, 36, 0, 0, "playGameButton"));
	mapEditorButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT + ButtonConstants::VERTICAL_SPACING, 238, 36, 0, 0, "mapEditorButton"));
	quitButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT*2 + ButtonConstants::VERTICAL_SPACING*2, 238, 36, 0, 0, "quitButton"));

	loadTextures();
}

MainMenu::~MainMenu()
{
}

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
