#pragma once
#include "Display.h"
#include "Object.h"
#include "SDLWrap.h"


class ImageObj : public Object
{
	Display m_disp;

public:

	ImageObj() {}

	ImageObj(Display display)
		:m_disp(display)
	{}


	Display GetDisplay() const { return m_disp; }

	virtual void Render(SDLWrap& renderer) const override { renderer.AddToDisplay(m_disp); }

	void SetDisplay(Display newDisplay) { m_disp = newDisplay; }

	virtual void SetPos(int x, int y) override { m_disp.SetTransformPos(x, y); }

	void SetFlip(SDL_RendererFlip flip) { m_disp.SetFlip(flip); }
};