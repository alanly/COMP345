#include "CharacterEditor.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "Character.h"
#include "dirent.h"
//#include "Map.h"
#include "MapEditor.h"

CharacterEditor::CharacterEditor(LoaderParameters* parameters) : GameObject(parameters)
{
	gotIt = false;
	d = new Director();
	tank = new TankCharacterBuilder();
	bully = new BullyCharacterBuilder();
	nimble = new NimbleCharacterBuilder();

	Button_Char_New = new GameObject(new LoaderParameters(80, 200, 204, 32, 0, 0, "Button_Char_New"));
	Button_Char_Load = new GameObject(new LoaderParameters(100, 250, 212, 32, 0, 0, "Button_Char_Load"));
	
	Button_Char_Play = new GameObject(new LoaderParameters(160, 450, 102, 52, 0, 0, "Button_Char_Play"));
	Button_Back = new GameObject(new LoaderParameters(0, 0, 96, 38, 0, 0, "Button_Back"));

	playerNameInput = new GameObject(new LoaderParameters(100, 120, 400, 40, 0, 0, "playerNameInput"));

	characterClassification = new GameObject(new LoaderParameters(80, 180, 100, 60, 0, 0, "characterClassification"));
	changeClassificationButton = new GameObject(new LoaderParameters(180, 195, 21, 19, 0, 0, "changeClassification"));

	strengthText = new GameObject(new LoaderParameters(80, 230, 200, 40, 0, 0, "strengthText"));
	strengthValue = new GameObject(new LoaderParameters(180, 230, 40, 40, 0, 0, "strengthValue"));

	dexterityText = new GameObject(new LoaderParameters(95, 260, 200, 40, 0, 0, "dexterityText"));
	dexterityValue = new GameObject(new LoaderParameters(195, 260, 40, 40, 0, 0, "dexterityValue"));

	charismaText = new GameObject(new LoaderParameters(110, 290, 200, 40, 0, 0, "charismaText"));
	charismaValue = new GameObject(new LoaderParameters(210, 290, 40, 40, 0, 0, "charismaValue"));

	inteligenceText = new GameObject(new LoaderParameters(125, 320, 200, 40, 0,0 , "inteligenceText"));
	inteligenceValue = new GameObject(new LoaderParameters(225, 320, 40, 40, 0, 0, "intelignceValue"));

	constitutionText = new GameObject(new LoaderParameters(140, 350, 200, 40, 0, 0, "constitutionText"));
	constitutionValue = new GameObject(new LoaderParameters(240, 350, 40, 40, 0, 0, "constitutionValue"));

	wisdomText = new GameObject(new LoaderParameters(155, 380, 200, 40, 0, 0, "wisdomText"));
	wisdomValue = new GameObject(new LoaderParameters(255, 380, 40, 40, 0, 0, "wisdomValue"));

	rollButton = new GameObject(new LoaderParameters(250, 280, 50, 50, 0, 0, "rollButton"));

	Char_Portrait = new GameObject(new LoaderParameters(225, 180, 47, 47, 0, 0, "Char_Portrait"));

	currentView = CharacterEditorView::ENTRY; 
	loadTextures();
}


CharacterEditor::~CharacterEditor()
{
}

void CharacterEditor::drawEntryView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Char_Choose"), Game::getInstance()->getRenderer());

	Button_Char_New->draw();
	Button_Char_Load->draw();

	Button_Back->getParameters()->setXPos(120);
	Button_Back->getParameters()->setYPos(300);
	Button_Back->draw();
}

void CharacterEditor::drawEditorView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Char_Create"), Game::getInstance()->getRenderer());

	Button_Back->getParameters()->setXPos(270);
	Button_Back->getParameters()->setYPos(450);
	Button_Back->draw();

	rollButton->draw();
	Button_Char_Play->draw();
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

	Char_Portrait->draw();

	loadCharacterTextures();
}

void CharacterEditor::drawSaveView()
{
}

void CharacterEditor::drawLoadView()
{
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Char_Load"), Game::getInstance()->getRenderer());

	Button_Back->getParameters()->setXPos(210);
	Button_Back->getParameters()->setYPos(450);
	Button_Back->draw();

	string curr_directory = "sav\\char\\";
	string extension = "xml";

	if(!gotIt){
		int currentX = 60;
		int currentY = 200;
		int incrementX = 10;
		int incrementY = 35;
		gotIt = true;
		DIR* dir_point = opendir(curr_directory.c_str());
        dirent* entry = readdir(dir_point);
        while (entry) { // if !entry then end of directory
               if (entry->d_type == DT_REG) { // if entry is a regular file
                   std::string fname = entry->d_name; // filename
                   // if filename's last characters are extension
                   if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos) {
					   // add filename to results vector
					   saves.push_back(new GameObject(new LoaderParameters(currentX, currentY, 300, 25, 0, 0, fname.substr(0, fname.length()-4))));
					   currentY += incrementY;
					   currentX += incrementX;
				   }
                }
                entry = readdir(dir_point);
        }
        loadSaveFiles();
	}
	drawSaveFiles();
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

void CharacterEditor::drawSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->draw();
        }
    }
}

void CharacterEditor::handleEntryViewEvents()
{
	Button_Char_New->handleEvents();
	Button_Char_Load->handleEvents();

	if (Button_Char_New->isClicked())
	{
		d->setCharacterBuilder(tank);
		d->constructCharacter("",1);
		c = d->getCharacter();
		currentView = CharacterEditorView::EDITOR;
		Button_Char_New->resetClicked();

		loadCharacterTextures();
	}
	if (Button_Char_Load->isClicked())
	{
		gotIt = false;
		currentView = CharacterEditorView::LOAD;
		Button_Char_Load->resetClicked();
	}
}

void CharacterEditor::handleEditorViewEvents()
{
	rollButton->handleEvents();
	changeClassificationButton->handleEvents();
	Button_Char_Play->handleEvents();

	if(rollButton->isClicked())
	{
		rollButton->resetClicked();
		string name = c->getName();
		enumUtility::characterClassifiction charClass = c->getClassification();
		c->~Character();
		switch(charClass){
			case enumUtility::Tank:
				d->setCharacterBuilder(tank);
				d->constructCharacter(name, 1);
				c = d->getCharacter();
			break;
			case enumUtility::Nimble:
				d->setCharacterBuilder(nimble);
				d->constructCharacter(name,1);
				c = d->getCharacter();
			break;
			case enumUtility::Bully:
				d->setCharacterBuilder(bully);
				d->constructCharacter(name, 1);
				c = d->getCharacter();
			break;
		}
	}
	if(changeClassificationButton->isClicked())
	{
		changeClassificationButton->resetClicked();
		if(c->getClassification() == enumUtility::Nimble)
		{
			d->setCharacterBuilder(tank);
			d->constructCharacter(c->getName(), c->getLevel());
			c = d->getCharacter();
		}
		else if(c->getClassification() == enumUtility::Tank)
		{
			d->setCharacterBuilder(bully);
			d->constructCharacter(c->getName(), c->getLevel());
			c = d->getCharacter();
		}
		else if(c->getClassification() == enumUtility::Bully)
		{
			d->setCharacterBuilder(nimble);
			d->constructCharacter(c->getName(), c->getLevel());
			c = d->getCharacter();
		}
	}
	if(Button_Char_Play->isClicked())
	{
		Button_Char_Play->resetClicked();
		if (c->getName() != "")
		{
			c->saveToFile();
			Game::getInstance()->setCurrentView(enumUtility::Game_Main);
		}
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
			if (name.length() < 8)
			{
				for (int i = 0; i < name.length(); i++)
				{
					name[i] = tolower(name[i]);
				}

				name += tolower(inputChar);
				name[0] = toupper(name[0]);
				c->setName(name);
			}
		}
	}
	
}

void CharacterEditor::handleSaveViewEvents()
{
}

void CharacterEditor::handleLoadViewEvents()
{
	for(vector<GameObject*>::const_iterator iter = saves.begin(); iter != saves.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->handleEvents();
			if((*iter)->isClicked())
			{
				(*iter)->resetClicked();
				//cout << (*iter)->getParameters()->getId() << " will be loaded change view to game view with new character" << endl;
				string filename = (*iter)->getParameters()->getId() + ".xml";
				c = c->readFromFile(filename);
				if(c != nullptr)
				{	

					Game::getInstance()->setCurrentView(enumUtility::Game_Main);
				}else{
					cout << "character is null " << endl;
				}
				
				//currentView = CharacterEditorView::MAP;
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
		case CharacterEditorView::MAP:

			break;
	}
	
}

void CharacterEditor::handleEvents() {
	Button_Back->handleEvents();

	if (Button_Back->isClicked())
	{
		switch (currentView)
		{
		case CharacterEditorView::ENTRY:
			Game::getInstance()->setCurrentView(enumUtility::gameView::Main_Menu);
			currentView = CharacterEditorView::ENTRY;
			break;
		case CharacterEditorView::EDITOR:
			currentView = CharacterEditorView::ENTRY;
			break;
		case CharacterEditorView::LOAD:
			currentView = CharacterEditorView::ENTRY;
			break;
		}
		Button_Back->resetClicked();
	} else {
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
}

void CharacterEditor::loadTextures() 
{
	TextureManager::getInstance()->load("img/game/btn/btn_char_new.png", Button_Char_New->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_char_load.png", Button_Char_Load->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_back.png", Button_Back->getParameters()->getId(), Game::getInstance()->getRenderer());
	
	TextureManager::getInstance()->load("img/game/ui/char_choose.png", "UI_Char_Choose", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/ui/char_load.png", "UI_Char_Load", Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/ui/char_create.png", "UI_Char_Create", Game::getInstance()->getRenderer());

	TextureManager::getInstance()->loadFont(strengthText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Strength");
	TextureManager::getInstance()->loadFont(dexterityText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Dexterity");
	TextureManager::getInstance()->loadFont(inteligenceText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Inteligence");
	TextureManager::getInstance()->loadFont(wisdomText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Wisdom");
	TextureManager::getInstance()->loadFont(constitutionText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Constitution");
	TextureManager::getInstance()->loadFont(charismaText->getParameters()->getId(),Game::getInstance()->getRenderer(), "Charisma");

	TextureManager::getInstance()->load("img/game/btn/btn_dice.png", rollButton->getParameters()->getId(), Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_next.png", changeClassificationButton->getParameters()->getId(),Game::getInstance()->getRenderer());
	TextureManager::getInstance()->load("img/game/btn/btn_char_play.png", Button_Char_Play->getParameters()->getId(), Game::getInstance()->getRenderer());
}

void CharacterEditor::loadCharacterTextures()
{
	TextureManager::getInstance()->loadFont(strengthValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getStrength()));
	TextureManager::getInstance()->loadFont(dexterityValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getDexterity()));
	TextureManager::getInstance()->loadFont(inteligenceValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getInteligence()));
	TextureManager::getInstance()->loadFont(wisdomValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getWisdom()));
	TextureManager::getInstance()->loadFont(constitutionValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getConstitution()));
	TextureManager::getInstance()->loadFont(charismaValue->getParameters()->getId(),Game::getInstance()->getRenderer(), to_string(c->getCharisma()));
		
	TextureManager::getInstance()->loadFont(playerNameInput->getParameters()->getId(),Game::getInstance()->getRenderer(), "Name: " + c->getName(), 30);

	string classification;
	switch(c->getClassification())
	{
		case enumUtility::Nimble:
			classification = "Nimble";
			TextureManager::getInstance()->load("img/game/portrait/portrait_cleric.png", Char_Portrait->getParameters()->getId(), Game::getInstance()->getRenderer());
			break;
		case enumUtility::Tank:
			classification = "Tank";
			TextureManager::getInstance()->load("img/game/portrait/portrait_fighter.png", Char_Portrait->getParameters()->getId(), Game::getInstance()->getRenderer());
			break;
		case enumUtility::Bully:
			classification = "Bully";
			TextureManager::getInstance()->load("img/game/portrait/portrait_thief.png", Char_Portrait->getParameters()->getId(), Game::getInstance()->getRenderer());
			break;
	}
	TextureManager::getInstance()->loadFont(characterClassification->getParameters()->getId(),Game::getInstance()->getRenderer(), classification, 34);
}

Character* CharacterEditor::getCharacter(){
	return this->c;
}