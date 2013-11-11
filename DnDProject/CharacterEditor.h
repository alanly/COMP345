#pragma once
#include "GameObject.h"
#include "Character.h"
#include "InputHandler.h"

class CharacterEditor : public GameObject
{
private:
	enum CharacterEditorView {ENTRY,
					EDITOR,
					SAVE,
					LOAD};
	GameObject* mainMenuButton;
	GameObject* newCharacterButton;
	GameObject* loadCharacterButton;


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
	GameObject* saveCharacterButton;
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

	void draw();
	void handleEvents();
	void loadTextures();
};

