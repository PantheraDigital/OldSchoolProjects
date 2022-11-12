#pragma once
#include "GameState.h"
#include "Object.h"
#include "UIButton.h"

class GameplayStateMachine;


class GameOver : public GameState
{
	GameplayStateMachine* m_pOwner;

	std::vector<Object*> m_displayList;

	std::vector<UIButton*> m_buttonSet;

public:
	GameOver(GameplayStateMachine* pOwner);
	~GameOver();

	void Render(SDLWrap& renderer) const override;

	bool HandleEvent(SDL_Event* pEvent) override;
};

