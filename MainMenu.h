#pragma once
#include <vector>

#include "GameState.h"
#include "Object.h"
#include "UIButton.h"

class GameplayStateMachine;

////////////////////////////////////////////
// Main menu state 
//  any input will exit this
////////////////////////////////////////////
class MainMenu : public GameState
{
	GameplayStateMachine* m_pOwner;

	//everything to display
	std::vector<Object*> m_displayList;

	//all buttons
	std::vector<UIButton*> m_buttonSet;


	void Deinitialize();

public:
	MainMenu(GameplayStateMachine* pOwner);
	~MainMenu();

	void Render(SDLWrap& renderer) const override;

	bool HandleEvent(SDL_Event* pEvent) override;
};
