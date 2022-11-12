#include "Display.h"

#include "ImageLoader.h"

Display::Display()
	:m_pTexture(nullptr)
	, m_transform({ 0,0,0,0 })
	, m_textureTransform({ 0,0,0,0 })
	, m_color({ 0,0,0,0 })
	, m_blend(SDL_BLENDMODE_BLEND)
	, m_flip(SDL_FLIP_NONE)
{}

Display::Display(std::shared_ptr<SDL_Texture> texture, bool useTextureSize)
	:Display()
{
	m_pTexture = texture;

	if (useTextureSize)
	{
		int w, h;
		SDL_QueryTexture(m_pTexture.get(), NULL, NULL, &w, &h);

		m_transform.h = h;
		m_transform.w = w;

		m_textureTransform.h = h;
		m_textureTransform.w = w;
	}
}

Display::Display(SDL_Rect rect, SDL_Color color)
	:m_pTexture(nullptr)
	, m_transform(rect)
	, m_textureTransform({ 0,0,0,0 })
	, m_color(color)
	, m_blend(SDL_BLENDMODE_BLEND)
	, m_flip(SDL_FLIP_NONE)
{}

Display::Display(std::shared_ptr<SDL_Texture> texture, SDL_Rect rect, SDL_Color color)
	:m_pTexture(texture)
	, m_transform(rect)
	, m_textureTransform({ 0,0,0,0 })
	, m_color(color)
	, m_blend(SDL_BLENDMODE_BLEND)
	, m_flip(SDL_FLIP_NONE)
{}

//text
Display::Display(const char* text, int size, SDL_Color color)
	:m_pTexture(nullptr)
	, m_transform({ 0,0,0,0 })
	, m_textureTransform({ 0,0,0,0 })
	, m_color(color)
	, m_blend(SDL_BLENDMODE_BLEND)
	, m_flip(SDL_FLIP_NONE)
{
	SetText(text, size, color);
}

//text with set transform
Display::Display(const char* text, int size, SDL_Color color, SDL_Rect transform)
	:Display(text, size, color)
{
	SetTransform(transform);
}


Display::~Display()
{
	m_pTexture.reset();
}

void Display::SetTexture(std::shared_ptr<SDL_Texture> texture)
{
	if (m_pTexture)
		m_pTexture.reset();

	if (texture)
		m_pTexture = texture;
	else
		m_pTexture = nullptr;
}

void Display::SetTransformPos(int x, int y)
{
	m_transform.x = x;
	m_transform.y = y;
}

void Display::SetTransformSize(int w, int h)
{
	m_transform.w = w;
	m_transform.h = h;
}

void Display::SetTextureTransformPos(int x, int y)
{
	m_textureTransform.x = x;
	m_textureTransform.y = y;
}
void Display::SetTextureTransformSize(int w, int h)
{
	m_textureTransform.w = w;
	m_textureTransform.h = h;
}

void Display::SetText(const char* text, int size, SDL_Color color)
{
	//get texture with text
	SetTexture(ImageLoader::GetInst()->GetTextImage(text, size, color));

	//set size
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(m_pTexture.get(), NULL, NULL, &texW, &texH);
	SetTransform(SDL_Rect({ 0,0, texW, texH }));
}