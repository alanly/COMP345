#pragma once
#include "GameObject.h"
#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include "dirent.h"
#include <iostream>

class MapList: public GameObject
{
	private:
		Map* map;
		vector<GameObject*> maps;
		bool gotIt;
	public:
		MapList(LoaderParameters* parameters);
		~MapList();

		void draw();
		void handleEvents();
		void loadTextures();
		void loadSaveFiles();
		void drawSaveFiles();
		Map* getMap();
};

