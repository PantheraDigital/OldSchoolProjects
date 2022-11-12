#pragma once
#include <memory>

#include "SDL.h"

///////////////////////////////////////
//stores info for SDL to render
/////////////////////////////////////////
class Display
{
	std::shared_ptr<SDL_Texture> m_pTexture;

	SDL_Rect m_textureTransform;//adjustment of texture
	SDL_Rect m_transform;//texture size and pos in renderer

	SDL_Color m_color;
	SDL_BlendMode m_blend;
	SDL_RendererFlip m_flip;

public:
	Display();

	//basic rectangle with color
	Display(SDL_Rect rect, SDL_Color color);

	//texture/ uses texture size or fills screen
	Display(std::shared_ptr<SDL_Texture> texture, bool useTextureSize);
	//texture with set transform and color overlay
	Display(std::shared_ptr<SDL_Texture> texture, SDL_Rect rect, SDL_Color color);

	//text
	Display(const char* text, int size, SDL_Color color);
	//text with set transform
	Display(const char* text, int size, SDL_Color color, SDL_Rect transform);

	~Display();


	SDL_Texture* GetTexture() const { return m_pTexture.get(); }
	SDL_Rect GetTransform() const { return m_transform; }
	SDL_Rect GetTextureTransform() const { return m_textureTransform; }
	SDL_Color GetColor() const { return m_color; }
	SDL_BlendMode GetBlend() const { return m_blend; }
	SDL_RendererFlip GetFlip() const { return m_flip; }

	void SetTexture(std::shared_ptr<SDL_Texture> texture);
	void SetTransform(SDL_Rect rect) { m_transform = rect; }
	void SetTextureTransform(SDL_Rect rect) { m_textureTransform = rect; }
	void SetColor(SDL_Color color) { m_color = color; }
	void SetBlendMode(SDL_BlendMode blendmode) { m_blend = blendmode; }
	void SetFlip(SDL_RendererFlip flip) { m_flip = flip; }

	void SetTransformPos(int x, int y);
	void SetTransformSize(int w, int h);

	void SetTextureTransformPos(int x, int y);
	void SetTextureTransformSize(int w, int h);

	void SetText(const char* text, int size, SDL_Color color);
};

