#pragma once
#include <map>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

////////////////////////////////
//loads and tracks already loaded images
//uses shared_ptr to self manage 
/////////////////////////////
class ImageLoader
{
	SDL_Renderer* m_pRenderer;

	//name, file path
	std::map<const char*, const char*> m_lookUpList;

	//name ,texture pointer
	std::map<const char*, std::shared_ptr<SDL_Texture>> m_imageList;

	ImageLoader(SDL_Renderer* renderer);

	ImageLoader();

public:

	static ImageLoader* GetInst();

	~ImageLoader();

	void SetRenderer(SDL_Renderer* renderer) { m_pRenderer = renderer; }

	std::shared_ptr<SDL_Texture> GetImage(const char* imageName);

	std::shared_ptr<SDL_Texture> GetTextImage(const char* text, int size, SDL_Color color);

};