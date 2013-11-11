#include "CharacterEditor.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "Character.h"
#include "ButtonConstants.h"
#include "dirent.h"

void CharacterEditor::determineEntryViewButtonPositions(int *initialX, int *initialY)
{
	// Determine the layout of buttons for the entry view
	*initialX = (Game::getInstance()->getWindowWidth() / 3) - (ButtonConstants::MEDIUM_WIDTH / 2);
	*initialY = (Game::getInstance()->getWindowHeight() / 3)
		+ (Game::getInstance()->getWindowHeight() / 3)/2
		- (ButtonConstants::MEDIUM_HEIGHT * 3 + ButtonConstants::VERTICAL_SPACING*2)/2;
}

CharacterEditor::CharacterEditor(LoaderParameters* parameters) : GameObject(parameters)
{
	// Determine the layout of buttons for the entry view
	int initialX = 0;
	int initialY = 0;
	ButtonConstants::determineInitialButtonPositions(&initialX, &initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 3, 3, 2);

	gotIt = false;
	newCharacterButton = new GameObject(new LoaderParameters(initialX, initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "newCharacterButton"));
	loadCharacterButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT + ButtonConstants::VERTICAL_SPACING, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "loadCharacterButton"));
	mainMenuButton = new GameObject(new LoaderParameters(initialX, initialY + ButtonConstants::MEDIUM_HEIGHT*2 + ButtonConstants::VERTICAL_SPACING*2, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 0, 0, "mainMenuButton"));

	//New view
	strengthText = new GameObject(new LoaderParameters(400,100,100,20,0,0,"strengthText"));
	strengthValue = new GameObject(new LoaderParameters(505,100,20,20,0,0,"strengthValue"));


	dexterityText = new GameObject(new LoaderParameters(400,120,100,20,0,0,"dexterityText"));
	dexterityValue = new GameObject(new LoaderParameters(505,120,20,20,0,0,"dexterityValue"));

	charismaText = new GameObject(new LoaderParameters(400,140,100,20,0,0,"charismaText"));
	charismaValue = new GameObject(new LoaderParameters(505,140,20,20,0,0,"charismaValue"));

	inteligenceText = new GameObject(new LoaderParameters(400,160,100,20,0,0,"inteligenceText"));
	inteligenceValue = new GameObject(new LoaderParameters(505,160,20,20,0,0,"intelignceValue"));

	constitutionText = new GameObject(new LoaderParameters(400,180,100,20,0,0,"constitutionText"));
	constitutionValue = new GameObject(new LoaderParameters(505,180,20,20,0,0,"constitutionValue"));

	wisdomText = new GameObject(new LoaderParameters(400,200,100,20,0,0,"wisdomText"));
	wisdomValue = new GameObject(new LoaderParameters(505,200,20,20,0,0,"wisdomValue"));

	rollButton = new GameObject(new LoaderParameters(100,100,ButtonConstants::SMALL_WIDTH,ButtonConstants::SMALL_HEIGHT,0,0,"rollButton"));
	playerNameInput = new GameObject(new LoaderParameters(200,100,120,20,0,0,"playerNameInput"));
	saveCharacterButton = new GameObject(new LoaderParameters(50,500,ButtonConstants::SMALL_WIDTH, ButtonConstants::SMALL_HEIGHT,0,0,"saveCharacterButton"));

	characterClassification = new GameObject(new LoaderParameters(400,50,75,20,0,0,"characterClassification"));
	changeClassificationButton = new GameObject(new LoaderParameters(500,50,60,40,0,0,"changeClassification"));

	currentView = CharacterEditorView::ENTRY; 
	loadTextures();
}


CharacterEditor::~CharacterEditor()
{
}

void CharacterEditor::drawEntryView()
{
	int initialX, initialY;
	ButtonConstants::determineInitialButtonPositions(&initialX, &initialY, ButtonConstants::MEDIUM_WIDTH, ButtonConstants::MEDIUM_HEIGHT, 3, 3, 2);

	mainMenuButton->getParameters()->setXPos(initialX);
	mainMenuButton->getParameters()->setYPos(initialY + ButtonConstants::MEDIUM_HEIGHT*2 + ButtonConstants::VERTICAL_SPACING*2);

	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "mainMenuBg"), Game::getInstance()->getRenderer());

	mainMenuButton->draw();
	newCharacterButton->draw();
	loadCharacterButton->draw();

}

void CharacterEditor::drawEditorView()
{
	mainMenuButton->getParameters()->setXPos(Game::getInstance()->getWindowWidth() / 2 - ButtonConstants::MEDIUM_WIDTH / 2);
	mainMenuButton->getParameters()->setYPos(Game::getInstance()->getWindowHeight() - ButtonConstants::VERTICAL_SPACING - ButtonConstants::MEDIUM_HEIGHT);
	mainMenuButton->draw();
	rollButton->draw();
	saveCharacterButton->draw();
	playerNameInput->draw();
	characterClassification->draw();
	changeClassificationButton->draw();
	strengthText->draw();
	strengthValue->draw();

	dexterityText->draw();
	dexterityValue->draw();

	wisdomText->draw();
	wisdomValue->draw();

	charismaText->draw();
	charismaValue->draw();

	inteligenceText->draw();
	inteligenceValue->draw();

	constitutionText->draw();
	constitutionValue->draw();
	loadCharacterTextures();
}

void CharacterEditor::drawSaveView()
{

}

void CharacterEditor::drawLoadView()
{
	string curr_directory = "saves\\character\\";
	string extension = "xml";
	//Getting the directory listing.
	if(!gotIt){
		int currentX = 100;
		int currentY = 100;
		int increment = 35;
		gotIt = true;
		DIR* dir_point = opendir(curr_directory.c_str());
        dirent* entry = readdir(dir_point);
        while (entry){                       // if !entry then end of directory
               if (entry->d_type == DT_REG){                // if entry is a regular file
                   std::string fname = entry->d_name;        // filename
                                                                                                // if filename's last characters are extension
                   if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos){
					   saves.push_back(new GameObject(new LoaderParameters(currentX,currentY,300,25,0,0,fname)));             // add filename to results vector
					   currentY += increment;
				   }
                }
                entry = readdir(dir_point);
        }
        loadSaveFiles();
	}
	mainMenuButton->draw();
	drawSaveFiles();
}
void CharacterEditor::drawSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
			//drawing the texture for each xml save file.
            (*iter)->draw();
        }
    }
}

void CharacterEditor::handleEntryViewEvents()
{
	newCharacterButton->handleEvents();
	loadCharacterButton->handleEvents();
	mainMenuButton->handleEvents();
	if (newCharacterButton->isClicked())
	{
		c = new Character("",1,enumUtility::Fighter);
		currentView = CharacterEditorView::EDITOR;
		newCharacterButton->resetClicked();
		loadCharacterTextures();
	}
	if (loadCharacterButton->isClicked())
	{
		//Load character
		gotIt = false;
		currentView = CharacterEditorView::LOAD;
		loadCharacterButton->resetClicked();
	}
	if(mainMenuButton->isClicked())
	{
		mainMenuButton->resetClicked();
		Game::getInstance()->setCurrentView(enumUtility::Main_Menu);
	}
}

//handles 
void CharacterEditor::handleEditorViewEvents()
{
	mainMenuButton->handleEvents();
	rollButton->handleEvents();
	changeClassificationButton->handleEvents();
	saveCharacterButton->handleEvents();
	if(mainMenuButton->isClicked())
	{
		mainMenuButton->resetClicked();
		currentView = CharacterEditorView::ENTRY;
		Game::getInstance()->setCurrentView(enumUtility::Main_Menu);
	}
	if(rollButton->isClicked())
	{
		rollButton->resetClicked();
		string name = c->getName();
		enumUtility::characterClassifiction charClass = c->getClassification();
		c->~Character();
		c = new Character(name,1,charClass);
	}
	if(changeClassificationButton->isClicked())
	{
		changeClassificationButton->resetClicked();
		if(c->getClassification() == enumUtility::Fighter)
		{
			c->setClassification(enumUtility::Mage);
		}
		else if(c->getClassification() == enumUtility::Mage)
		{
			c->setClassification(enumUtility::Tank);
		}
		else if(c->getClassification() == enumUtility::Tank)
		{
			c->setClassification(enumUtility::Fighter);
		}
	}
	if(saveCharacterButton->isClicked())
	{
		saveCharacterButton->resetClicked();
		c->saveToFile();
		std::cout << "saving character object" << endl;

		Game::getInstance()->setCurrentView(enumUtility::Game_Main);
	}
	string input = InputHandler::getInstance()->getInput();

	if (input != "") {
		string name = c->getName();
		char inputChar = input[0];

		// Handle backspace events
		if (input == "Backspace") {
			if (name.length() > 1)
				c->setName(name.substr(0, name.length() - 1));
			else
				c->setName(string());
		}

		// Ensure we only get alphabetical characters.
		if (input.length() == 1 && inputChar >= 'A' && inputChar <= 'Z') {
			if (name.length() <= 8)
				c->setName(name + input);
		}
	}
	
}

void CharacterEditor::handleSaveViewEvents()
{
}

void CharacterEditor::handleLoadViewEvents()
{
	mainMenuButton->handleEvents();
	if(mainMenuButton->isClicked())
	{
		mainMenuButton->resetClicked();
		currentView = CharacterEditorView::ENTRY;
		Game::getInstance()->setCurrentView(enumUtility::Main_Menu);
	}
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->handleEvents();
			if((*iter)->isClicked())
			{
				(*iter)->resetClicked();
				cout << (*iter)->getParameters()->getId() << " will be loaded change view to game view with new character" << endl;
			}
        }
    }
}

void CharacterEditor::draw() {
	switch (currentView)
	{
		case CharacterEditorView::ENTRY:
			drawEntryView();
			break;
		case CharacterEditorView::EDITOR:
			drawEditorView();
			break;
		case CharacterEditorView::LOAD:
			drawLoadView();
			break;
	}
	
}
void CharacterEditor::handleEvents() {
	switch (currentView)
	{
	case CharacterEditorView::ENTRY:
		handleEntryViewEvents();
		break;
	case CharacterEditorView::EDITOR:
		handleEditorViewEvents();
		break;
	case CharacterEditorView::LOAD:
		handleLoadViewEvents();
		break;
	}
}
void CharacterEditor::loadTextures() 
{
	// Load textures for entry view.
	TextureManager::getInstance()->load("images/buttons/new_character_medium.png", newCharacterButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/load_character_medium.png", loadCharacterButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/buttons/main_menu_medium.png", mainMenuButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/main-screen.png", "mainMenuBg", Game::getInstance()->getRenderer());

	TextureManager::getInstance()->loadFont(strengthText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Strength");
	TextureManager::getInstance()->loadFont(dexterityText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Dexterity");
	TextureManager::getInstance()->loadFont(inteligenceText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Inteligence");
	TextureManager::getInstance()->loadFont(wisdomText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Wisdom");
	TextureManager::getInstance()->loadFont(constitutionText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Constitution");
	TextureManager::getInstance()->loadFont(charismaText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Charisma");
	TextureManager::getInstance()->load("images/buttons/roll_small.png", rollButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/Character-editor/change.png",changeClassificationButton->getParameters()->getId(),Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("images/Character-editor/save.png",saveCharacterButton->getParameters()->getId(),Game::getInstance()->getRenderer());
	
}
void CharacterEditor::loadSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            TextureManager::getInstance()->loadFont((*iter)->getParameters()->getId(),Game::getInstance()->getRenderer(), (*iter)->getParameters()->getId());
        }
    }
}
void CharacterEditor::loadCharacterTextures()
{
	TextureManager::getInstance()->loadFont(strengthValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getStrength()));
	TextureManager::getInstance()->loadFont(dexterityValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getDexterity()));
	TextureManager::getInstance()->loadFont(inteligenceValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getInteligence()));
	TextureManager::getInstance()->loadFont(wisdomValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getWisdom()));
	TextureManager::getInstance()->loadFont(constitutionValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getConstitution()));
	TextureManager::getInstance()->loadFont(charismaValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getCharisma()));

	TextureManager::getInstance()->loadFont(playerNameInput->getParameters()->getId(),Game::getInstance()->getRenderer(), c->getName());

	string classification;
	switch(c->getClassification())
	{
		case enumUtility::Fighter:
			classification = "Fighter";
			break;
		case enumUtility::Mage:
			classification = "Mage";
			break;
		case enumUtility::Tank:
			classification = "Tank";
			break;
	}
	TextureManager::getInstance()->loadFont(characterClassification->getParameters()->getId(),Game::getInstance()->getRenderer(), classification);

}