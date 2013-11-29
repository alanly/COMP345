#pragma once
#include "GameObject.h"
#include "Character.h"
#include "InputHandler.h"
#include "Director.h"
#include "BullyCharacterBuilder.h"
#include "TankCharacterBuilder.h" 
#include "NimbleCharacterBuilder.h"

class CharacterEditor : public GameObject
{
private:
	enum CharacterEditorView {ENTRY,
					EDITOR,
					SAVE,
					LOAD,
					MAP};

	GameObject* Button_Back;
	GameObject* Button_Char_New;
	GameObject* Button_Char_Load;

	GameObject* Button_Char_Play;

	GameObject* strengthText;
	GameObject* dexterityText;
	GameObject* inteligenceText;
	GameObject* wisdomText;
	GameObject* charismaText;
	GameObject* constitutionText;


	GameObject* strengthValue;
	GameObject* inteligenceValue;
	GameObject* dexterityValue;
	GameObject* charismaValue;
	GameObject* wisdomValue;
	GameObject* constitutionValue;
	
	GameObject* characterClassification;
	GameObject* changeClassificationButton;
	GameObject* rollButton;

	GameObject* Char_Portrait;

	Director* d;
	TankCharacterBuilder* tank;
	NimbleCharacterBuilder* nimble;
	BullyCharacterBuilder* bully;

	GameObject* playerNameInput;
	bool gotIt;
	CharacterEditorView  currentView;
	Character *c;
	void loadCharacterTextures();
	void loadSaveFiles();
	void drawSaveFiles();
	vector<GameObject*> saves;
	void determineEntryViewButtonPositions(int*, int*);

public:
	CharacterEditor(LoaderParameters* parameters);
	~CharacterEditor();

	void drawEntryView();
	void drawEditorView();
	void drawSaveView();
	void drawLoadView();

	void handleEntryViewEvents();
	void handleEditorViewEvents();
	void handleSaveViewEvents();
	void handleLoadViewEvents();
	Character* getCharacter();
	void draw();
	void handleEvents();
	void loadTextures();
};

