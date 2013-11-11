#pragma once
#include "SDL_image.h"
#include "SDL.h"
#include <iostream>
#include <string.h>


namespace SDL_Utilities
{
	void logSDLError(std::string);
	SDL_Texture* loadTexture(std::string, SDL_Renderer*);
	void renderTexture(SDL_Texture*, SDL_Renderer*, SDL_Rect , SDL_Rect* = nullptr);
	void renderTexture(SDL_Texture*, SDL_Renderer*, int , int, SDL_Rect* = nullptr);
}