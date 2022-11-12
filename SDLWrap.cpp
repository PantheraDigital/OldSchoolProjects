#include "SDLWrap.h"

#include <SDL_ttf.h>
#include <iostream>
#include <chrono>

//use these for paralx scrolling
//Focus does not get affected by paralax
//background moves slow and foreground fast
#define BACKGROUND = 2;//3 layers of background
#define FOCUS = 6;//4 layers focused on
#define FOREGROUND = 9;//3 layers in foreground


SDLWrap::SDLWrap()
	:m_kMaxLayer(9)
	, m_lastUsedLayer(NULL)
	, m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, pMusic(nullptr)
	, m_pLoader(ImageLoader::GetInst())
	, m_backColor({0,0,0,255})
	, m_dispLimitX(0)
	, m_dispLimitY(0)
{
	std::vector<Display> row;
	m_displayList.push_back(row);
}

SDLWrap::~SDLWrap()
{
	Deinitialize();

	Mix_FreeMusic(pMusic);//////
	Mix_CloseAudio();///////////
}

//////////////////////////////
//initialize sdl and renderer with default values
//returns true if successful
//////////////////////////
bool SDLWrap::Initialize()
{
	return Initialize(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
}

//////////////////////////////
//initialize sdl and renderer with a set position and size
//returns true if successful
//////////////////////////
bool SDLWrap::Initialize(int x, int y, int w, int h)
{
	//check if SDL works
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Faild to initialize SDL" << std::endl;
		return false;
	}

	TTF_Init();

	//create window
	m_pWindow = SDL_CreateWindow("Hello World", x, y, w, h, SDL_WINDOW_RESIZABLE);
	//check if window was set up
	if (m_pWindow != nullptr)
	{
		std::cout << "SDL_CreateWindow() succeeded" << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateWindow() faild. Error" << SDL_GetError() << std::endl;
		SDL_Quit();
		system("pause");
		return false;
	}

	//create renderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	//check renderer
	if (m_pRenderer != nullptr)
	{
		std::cout << "SDL_CreateRenderer() succeeded" << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateRenderer() faild. Error" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return false;
	}

	////////wav
	int error = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if (error != 0)
	{
		std::cout << "Mix open audio faild. error:" << Mix_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return error;
	}

	int audioFlags = MIX_INIT_MP3;
	error = Mix_Init(audioFlags);
	if (error != audioFlags)
	{
		std::cout << "Mix init faild. error:" << Mix_GetError() << std::endl;
		Mix_CloseAudio();
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return error;
	}

	pMusic = Mix_LoadMUS("assets/foo.mp3");

	if (pMusic == nullptr)
	{
		std::cout << "failed to load music. error: " << Mix_GetError() << std::endl;
	}
	else
	{
		Mix_PlayMusic(pMusic, -1);
	}

	////

	//allow alpha to work
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetLogicalSize(m_pRenderer, 640, 480);//640, 480

	m_pLoader->SetRenderer(m_pRenderer);
	return true;
}

/////////////////////////////////
//destroy sdl, renderer, and clear shapes
///////////////////////////////
void SDLWrap::Deinitialize()
{
	ClearDisplayList();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TTF_Quit();//before sdl quit
	SDL_Quit();
}

/////////////////////////
//return index of layer and pos
//////////////////////////////
int SDLWrap::FindDisplayAt(Display target, short layer)
{
	if (layer <= m_kMaxLayer)
	{
		for (unsigned int j = 0; j < m_displayList[layer].size(); ++j)
		{
			if (CompairDisplays(target, m_displayList[layer][j]))
			{
				return j;
			}
		}
	}

	return -1;
}

std::pair<int, int> SDLWrap::FindDisplay(Display target)
{
	for (unsigned int i = 0; i < m_displayList.size(); ++i)
	{
		for (unsigned int j = 0; j < m_displayList[i].size(); ++j)
		{
			if (CompairDisplays(target, m_displayList[i][j]))
			{
				return { i,j };
			}
		}
	}
	return { -1,-1 };
}

/////////////////////////////
//return if Displays are the same
/////////////////////////////////
bool SDLWrap::CompairDisplays(Display disp1, Display disp2)
{
	if (disp1.GetTexture() == disp2.GetTexture())
	{
		if (disp1.GetTransform().x == disp2.GetTransform().x && disp1.GetTransform().y == disp2.GetTransform().y && disp1.GetTransform().w == disp2.GetTransform().w && disp1.GetTransform().h == disp2.GetTransform().h)
		{
			if (disp1.GetColor().r == disp2.GetColor().r && disp1.GetColor().g == disp2.GetColor().g && disp1.GetColor().b == disp2.GetColor().b && disp1.GetColor().a == disp2.GetColor().a)
				return true;
			else
				return false;
		}
	}
	return false;
}

///////////////////////////////
//prepaires a layer if there is none and changes layer passed in if to large
//////////////////////////////////////
short SDLWrap::GetLayerIndex(short layer)
{
	if (layer > m_kMaxLayer)
		layer = m_kMaxLayer;

	while (layer >= (int)m_displayList.size())
	{
		std::vector<Display> row;
		m_displayList.push_back(row);
	}

	return layer;
}

//////////////////////////////
//uses FindDisplay to locate then move a Display target
/////////////////////////////////
void SDLWrap::MoveToLayer(Display target, short layer)
{
	layer = GetLayerIndex(layer);

	//erase shape from old pos
	RemoveDisplay(target, layer);
	//add shape to new pos
	AddToDisplay(target, layer);
}

////////////////////////////
//clears all elements from m_displayList
////////////////////////////////
void SDLWrap::ClearDisplayList()
{
	for (unsigned int i = 0; i < m_displayList.size(); ++i)
	{
		m_displayList[i].clear();
	}
	m_displayList.clear();
}

///////////////////////////////
//locates the removes display from m_displayList by using FindDisplay
//////////////////////////////////
void SDLWrap::RemoveDisplay(Display target, short layer)
{
	int index = FindDisplayAt(target, layer);
	if (index < NULL)
		return;

	m_displayList[layer].erase(m_displayList[layer].begin() + index);
}
void SDLWrap::RemoveDisplay(Display target)
{
	std::pair<int, int> index = FindDisplay(target);

	if (index.first < NULL)
		return;

	m_displayList[index.first].erase(m_displayList[index.first].begin() + index.second);
}

///////////////////////////
//Render m_displayList starting at layer 0
////////////////////////////////
void SDLWrap::Draw()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);
	//render back
	SDL_RenderClear(m_pRenderer);

	RenderDispList();

	SDL_RenderPresent(m_pRenderer);
}

//////////////////////////////
//uses ImageLoader to retrive texture by name
///////////////////////////////////
std::shared_ptr<SDL_Texture> SDLWrap::LoadTexture(const char* imageName)
{
	return m_pLoader->GetImage(imageName);
}

/////////////////////////////////
//insert display into m_displayList at layer
//////////////////////////////////
void SDLWrap::AddToDisplay(Display display, short layer)
{
	if (layer == 0)
	{
		int x, y;
		SDL_QueryTexture(display.GetTexture(), NULL, NULL, &x, &y);

		if (m_dispLimitX < x)
			m_dispLimitX = x;

		if (m_dispLimitY < y)
			m_dispLimitY = y;
	}

	layer = GetLayerIndex(layer);
	m_displayList[layer].push_back(display);
	m_lastUsedLayer = layer;
}
void SDLWrap::AddToDisplay(Display display)
{
	AddToDisplay(display, m_lastUsedLayer);
}
void SDLWrap::AddToDisplay(std::vector<Display> display)
{
	for (int i = 0; i < display.size(); ++i)
	{
		AddToDisplay(display[i], m_lastUsedLayer);
	}
}
void SDLWrap::AddToDisplay(std::vector<Display> display, short layer)
{
	for (int i = 0; i < display.size(); ++i)
	{
		AddToDisplay(display[i], layer);
	}
}

/////////////////////////////////////
//prepares all elements in m_displayList to be drawn
//////////////////////////////////
void SDLWrap::RenderDispList()
{
	for (int i = 0; i < m_displayList.size(); ++i)
	{
		for (int j = 0; j < m_displayList[i].size(); ++j)
		{
			if (m_displayList[i][j].GetTexture())
			{
				SDL_SetTextureBlendMode(m_displayList[i][j].GetTexture(), m_displayList[i][j].GetBlend());//set blendmode

				if (m_displayList[i][j].GetColor().a > 0)
				{
					//adjust color
					SDL_Color tempColor = m_displayList[i][j].GetColor();
					SDL_SetTextureAlphaMod(m_displayList[i][j].GetTexture(), tempColor.a);
					SDL_SetTextureColorMod(m_displayList[i][j].GetTexture(), tempColor.r, tempColor.g, tempColor.b);
				}

				if (m_displayList[i][j].GetTransform().h > 0 && m_displayList[i][j].GetTransform().w > 0)//check transform
				{
					if (m_displayList[i][j].GetTextureTransform().h > 0 && m_displayList[i][j].GetTextureTransform().w > 0)//check for texture transform
					{
						SDL_RenderCopyEx(m_pRenderer, m_displayList[i][j].GetTexture(), &m_displayList[i][j].GetTextureTransform(), &m_displayList[i][j].GetTransform(), 0, nullptr, m_displayList[i][j].GetFlip());
					}
					else//no texture transform
						SDL_RenderCopyEx(m_pRenderer, m_displayList[i][j].GetTexture(), nullptr, &m_displayList[i][j].GetTransform(), 0, nullptr, m_displayList[i][j].GetFlip());
				}
				else//no transform// will fill screen
					SDL_RenderCopyEx(m_pRenderer, m_displayList[i][j].GetTexture(), nullptr, nullptr, 0, nullptr, m_displayList[i][j].GetFlip());

			}
			else if (m_displayList[i][j].GetTransform().h > 0 && m_displayList[i][j].GetTransform().w > 0)//basic rect and color
			{
				SDL_SetRenderDrawBlendMode(m_pRenderer, m_displayList[i][j].GetBlend());

				SDL_Color temp = m_displayList[i][j].GetColor();
				SDL_SetRenderDrawColor(m_pRenderer, temp.r, temp.g, temp.b, temp.a);

				SDL_RenderFillRect(m_pRenderer, &m_displayList[i][j].GetTransform());

				SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
			}
		}
	}
}

void SDLWrap::UpdateCamera(SDL_Rect cameraTransform)
{
	m_camera.x = cameraTransform.x - 256;
	m_camera.y = cameraTransform.y - 160;
	/*
	if (m_camera.x < 0)
		m_camera.x = 0;

	if (m_camera.y < 0)
		m_camera.y = 0;

	if (m_camera.x + m_camera.w >= m_dispLimitX)
		m_camera.x = m_dispLimitX - m_camera.w;

	if (m_camera.y + m_camera.h >= m_dispLimitY)
		m_camera.y = m_dispLimitY - m_camera.h;*/
}

SDL_Rect SDLWrap::GetCamRelitivePos(SDL_Rect transform)//////////////probably dont need
{
	transform.x -= m_camera.x;
	transform.y -= m_camera.y;
	return transform;
}