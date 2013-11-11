#include "MainMenu.h"
#include "TextureManager.h"
#include "ButtonConstants.h"
#include "Game.h"

void MainMenu::determineEntryViewButtonPositions(int *initialX, int *initialY)
{
	// Determine the layout of buttons for the entry view
	*initialX = (Game::getInstance()->getWindowWidth() / 3) - (ButtonConstants::MEDIUM_WIDTH / 2);
	*initialY = (Game::getInstance()->getWindowHeight() / 3)
		+ (Game::getInstance()->getWindowHeight() / 3)/2
		- (ButtonConstants::MEDIUM_HEIGHT * 3 + ButtonConstants::VERTICAL_SPACING*2)/2;
}

MainMenu::MainMenu(LoaderParameters* parameters) : GameObject(parameters)
{
	// Determine the layout of buttons.
	int initialX = 0;
	int initialY = 0;
	determineEntryViewButtonPositions(&initialX, &initialY);

	playGameButton = new GameObject(new LoaderParameters(initialX, initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "playGameButton"));
	mapEditorButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT + ButtonConstants::VERTICAL_SPACING, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "mapEditorButton"));
	quitButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT*2 + ButtonConstants::VERTICAL_SPACING*2, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "quitButton"));

	loadTextures();
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "mainMenuBg"), Game::getInstance()->getRenderer());
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
	}
	if (mapEditorButton->isClicked())
	{
		Game::getInstance()->setCurrentView(enumUtility::Map_Editor);
		mapEditorButton->resetClicked();
	}
	if (quitButton->isClicked())
	{
		Game::getInstance()->quit();
	}
}

void MainMenu::loadTextures()
{
	TextureManager::getInstance()->load("images/buttons/new_game_medium.png", playGameButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/map_editor_medium.png", mapEditorButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/quit_game_medium.png", quitButton->getParameters()->getId(), Game::getInstance()->getRenderer());

	TextureManager::getInstance()->load("images/main-screen.png", "mainMenuBg", Game::getInstance()->getRenderer());
}
