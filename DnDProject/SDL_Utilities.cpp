#include "SDL_Utilities.h"

namespace SDL_Utilities
{

	/**
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message too
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	void logSDLError(std::string msg)
	{
		std::cout << &msg << " error: " << SDL_GetError() << std::endl;
	}

	SDL_Texture* loadTexture(std::string file, SDL_Renderer *ren)
	{
		SDL_Texture *texture = IMG_LoadTexture(ren,file.c_str());
		return texture;
	}

	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip)
	{
		SDL_RenderCopy(ren, tex, clip, &dst);
	}

	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip)
	{
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		if(clip != nullptr)
		{
			dst.w = clip->w;
			dst.h = clip->h;
		}else
		{
			SDL_QueryTexture(tex,NULL,NULL,&dst.w, &dst.h);
		}
		renderTexture(tex,ren,dst,clip);
	}
}