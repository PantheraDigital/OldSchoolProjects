#pragma once
#include <functional>

#include "Object.h"
#include "Display.h"


class UIButton : public Object
{
private:
	
	Display m_disp;

	Display m_highlightedDisp;

	bool m_isHighlighted;

	//makes invisable and prevents interaction
	bool m_hidden;


	//trigger function
	std::function<void()> m_callback;


	bool HitTest(int x, int y);

public:
	UIButton(SDL_Rect transform, Display neutralDisplay, Display highlightDisplay);
	~UIButton();


	void Render(SDLWrap& renderer) const;

	virtual Display GetDisplay() const override;

	virtual void HandleEvent(SDL_Event* pEvent) override;

	void Trigger();

	void SetCallback(std::function<void()> callback) { m_callback = callback; }

	void SetIsHighlighted(bool value) { m_isHighlighted = value; }

	void SetHidden(bool hidden) { m_hidden = hidden; }

};

