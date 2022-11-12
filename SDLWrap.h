#pragma once

#include <SDL.h>
#include <vector>

#include "Display.h"
#include "ImageLoader.h"

#include "SDL_Mixer.h" //if error with forward declaration
//struct Mix_Music;//

//////////////////////////////////////
//contains functions for displaying textures and rects to the window
//not responsible for pointers passed in
////////////////////////////////
class SDLWrap
{
	const short m_kMaxLayer;
	int m_lastUsedLayer;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	ImageLoader* m_pLoader;

	Mix_Music* pMusic;///

	//window background color
	SDL_Color m_backColor;

	SDL_Rect m_camera;
	int m_dispLimitX;
	int m_dispLimitY;

	std::vector <std::vector<Display>> m_displayList;


	//return the layer and pos of a shape
	std::pair<int, int> FindDisplay(Display target);
	int FindDisplayAt(Display target, short layer);

	bool CompairDisplays(Display disp1, Display disp2);

	short GetLayerIndex(short layer);

	void RenderDispList();
	SDL_Rect GetCamRelitivePos(SDL_Rect transform);

public:
	SDLWrap();

	~SDLWrap();

	//initialize sdl and renderer with default values
	//returns true if successful
	bool Initialize();
	//initialize sdl with specified perams and renderer with default values
	bool Initialize(int x,int y,int w,int h);

	//destroy sdl, renderer, and clear shapes
	void Deinitialize();

	void AddToDisplay(Display display);
	void AddToDisplay(Display display, short layer);
	void AddToDisplay(std::vector<Display> display);
	void AddToDisplay(std::vector<Display> display, short layer);

	//move a shape to a different layer
	void MoveToLayer(Display target, short layer);

	//removes shape from list/ does not delete pointer
	void RemoveDisplay(Display target);
	void RemoveDisplay(Display target, short layer);

	//empty list of shapes/ deletes pointers
	void ClearDisplayList();

	//draw all shapes in all layers
	void Draw();

	void GetDisplaySize(int& w, int& h) { SDL_RenderGetLogicalSize(m_pRenderer, &w, &h); }
	std::shared_ptr<SDL_Texture> LoadTexture(const char* imageName);

	SDL_Renderer* GetRenderer() { return m_pRenderer; }

	void UpdateCamera(SDL_Rect cameraTransform);
};

