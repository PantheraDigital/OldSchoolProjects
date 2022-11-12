#include "ImageLoader.h"

#include <SDL_ttf.h>

ImageLoader* ImageLoader::GetInst()
{
	static ImageLoader* instance = new ImageLoader();

	return instance;
}


ImageLoader::ImageLoader(SDL_Renderer* renderer)
	:m_pRenderer(renderer)
{
}

ImageLoader::ImageLoader()
	: m_pRenderer(nullptr)
{
	m_lookUpList = std::map<const char*, const char*>{
		{"NoImage", "Assets/NoImage.gif"}
		,{"background", "Assets/background.jpg"}
		,{"adventurer  ", "Assets/adventurerSheet.png"}
		,{"spikes", "Assets/spikes.png"}
		,{"tile", "Assets/tile.png"}
		,{"tileCracked", "Assets/tileCracked.png"}
		,{"spikeSheet", "Assets/spikeSheet.png"}
		,{"charTest", "Assets/charTest.png"}
		,{"PHMenu", "Assets/PHMenu.jpg"}
		,{"PHGameover", "Assets/PHGameOver.jpg"}
		,{"BGBack", "Assets/BGBack.png"}
		,{"BGFront", "Assets/BGFront.png"}
		,{"CloudsBack", "Assets/CloudsBack.png"}
		,{"CloudsFront", "Assets/CloudsFront.png"}
		,{"Tileset", "Assets/Tileset.png"}
	};
}

ImageLoader::~ImageLoader()
{
	m_pRenderer = nullptr;
}

/////////////////////////////
//loads or finds texture
//returns a default texture if imageName was bad
///////////////////////////////
std::shared_ptr<SDL_Texture> ImageLoader::GetImage(const char* imageName)
{
	if (m_lookUpList.count(imageName))
	{
		if (m_imageList.count(imageName))
		{
			return m_imageList.at(imageName);
		}
		else
		{
			SDL_Surface* rSurface = IMG_Load(m_lookUpList.at(imageName));
			if (rSurface)
			{

				std::shared_ptr<SDL_Texture> temp((SDL_CreateTextureFromSurface(m_pRenderer, rSurface)), [](SDL_Texture* t) {SDL_DestroyTexture(t); });
				SDL_FreeSurface(rSurface);

				m_imageList.emplace(imageName, temp);
				return m_imageList.at(imageName);
			}
		}
	}

	return GetImage("NoImage");
}

/////////////////////////////////
//create and return a texture with text
//////////////////////////////////////
std::shared_ptr<SDL_Texture> ImageLoader::GetTextImage(const char* text, int size, SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont("Fonts/arial.ttf", size);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	TTF_CloseFont(font);

	std::shared_ptr<SDL_Texture> temp((SDL_CreateTextureFromSurface(m_pRenderer, surface)), [](SDL_Texture* t) {SDL_DestroyTexture(t); });
	SDL_FreeSurface(surface);

	return temp;
}