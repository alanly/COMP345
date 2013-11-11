#include "TextureManager.h"
#include <SDL_image.h>
#include "SDL_Utilities.h"
TextureManager* TextureManager::instance = nullptr;

void TextureManager::draw(LoaderParameters* parameters, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

	sourceRect.x = parameters->getWidth() * parameters->getColumn();
	sourceRect.y = parameters->getHeight() * parameters->getRow();
	sourceRect.w = parameters->getWidth();
	sourceRect.h = parameters->getHeight();

	destinationRect.x = parameters->getXPos();
	destinationRect.y = parameters->getYPos();
	destinationRect.w = parameters->getWidth();
	destinationRect.h = parameters->getHeight();

	if (textureMap.find(parameters->getId() + string("_font")) != textureMap.end()) {
		SDL_QueryTexture(textureMap[parameters->getId() + string("_font")], nullptr, nullptr, &destinationRect.w, &destinationRect.h);
		SDL_RenderCopyEx(renderer, textureMap[parameters->getId() + string("_font")], &sourceRect, &destinationRect, 0, 0, flip);
		return;
	}

	SDL_RenderCopyEx(renderer, textureMap[parameters->getId()], &sourceRect, &destinationRect, 0, 0, flip);
}

bool TextureManager::load(const string &fileName, string id, SDL_Renderer* renderer)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, fileName.c_str());

	if (texture != 0)
	{
		textureMap[id] = texture;
		return true;
	}

	return false;
}
bool TextureManager::loadFont(string id, SDL_Renderer* renderer,string message) 
{
	if (message == "") message = " ";

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("res/GillSansMTPro-Book.otf", 18);
	
	SDL_Color color = {255,0,0};		
	SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	TTF_CloseFont(font);
	SDL_FreeSurface(surface);

	if(texture != 0)
	{
		textureMap[id + std::string("_font")] = texture;
		return true;
	}
	return false;
}
TextureManager* TextureManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}