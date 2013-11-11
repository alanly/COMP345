#pragma once

#include <SDL.h>
#include <string>
#include <map>
#include "SDL_ttf.h"
#include "LoaderParameters.h"

using namespace std;

class TextureManager
{
private:
	TextureManager() {};

	// This is a singleton class.
	static TextureManager* instance;

	// All of the textures will be loaded and inserted into this map.
	map<string, SDL_Texture*> textureMap;

public:
	~TextureManager();

	// Overloaded draw function that uses the given row and column of the spritesheet/texture to draw to the screen.
	void draw(LoaderParameters* parameters, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	// Loads a resource (image) to be used a sprite or spritesheet later.
	bool load(const string &fileName, string id, SDL_Renderer* renderer);
	bool loadFont(string id, SDL_Renderer* renderer,string message);
	// Singleton function.
	static TextureManager* getInstance();
};

