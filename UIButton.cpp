#include "UIButton.h"

#include "SDLWrap.h"
//#include <iostream>

UIButton::UIButton(SDL_Rect transform, Display neutralDisplay, Display highlightDisplay)
	: m_disp(neutralDisplay)
	, m_highlightedDisp(highlightDisplay)
	, m_isHighlighted(false)
	, m_hidden(false)
{
	m_disp.SetTransform(transform);
	m_highlightedDisp.SetTransform(transform);
}

UIButton::~UIButton()
{
}


void UIButton::Render(SDLWrap& renderer) const
{
	renderer.AddToDisplay(GetDisplay());
}

////////////////////////////////////
//return button display based on state
////////////////////////////////////////////////////
Display UIButton::GetDisplay() const
{
	if (m_hidden)
		return Display();

	if (m_isHighlighted)
		return m_highlightedDisp;
	else
		return m_disp;
}

/////////////////////////////////////////////
//determins button behavior based on events
///////////////////////////////////////////////
void UIButton::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_MOUSEMOTION:
	{
		//check if mouse is touching
		m_isHighlighted = HitTest(pEvent->button.x, pEvent->button.y);

		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	{
		if (m_callback != nullptr)
		{
			if (HitTest(pEvent->button.x, pEvent->button.y))
			{
				m_callback();
			}
		}
	}


	}
}

void UIButton::Trigger()
{
	if (m_callback != nullptr && !m_hidden)
		m_callback();
}

bool UIButton::HitTest(int x, int y)
{
	if (m_hidden)
		return false;

	return (x > m_disp.GetTransform().x && x < m_disp.GetTransform().x + m_disp.GetTransform().w &&
		y > m_disp.GetTransform().y && y < m_disp.GetTransform().y + m_disp.GetTransform().h);
}