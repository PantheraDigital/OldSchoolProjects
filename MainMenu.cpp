#include "MainMenu.h"

#include "GameplayStateMachine.h"
#include "Game.h"
#include "ImageLoader.h"
#include "ImageObj.h"
#include "SDLWrap.h"

#include "ButtonFunctions.h"


MainMenu::MainMenu(GameplayStateMachine* pOwner)
	: m_pOwner(pOwner)
{
	m_displayList.push_back(new ImageObj(Display(SDL_Rect{ 0,0,0,0 }, SDL_Color{72,72,246,255})) );

	// Play Button////////////////////
	SDL_Rect transform{ 300, 200, 50, 25 };
	Display buttonDisp(transform, SDL_Color{ 64, 64, 64, SDL_ALPHA_OPAQUE });
	Display buttonHighlightDisp(transform, SDL_Color{ 128, 128, 128, SDL_ALPHA_OPAQUE });

	UIButton* pPlayButton = new UIButton(transform, buttonDisp, buttonHighlightDisp);
	pPlayButton->SetCallback(GameplayStateChange(pOwner, GameplayStateMachine::SceneName::kGameplay));

	Display playText("Play", 100, SDL_Color{ 255, 255, 255, 255 }, SDL_Rect{ 300, 200, 50, 25 });

	m_displayList.push_back(pPlayButton);
	m_displayList.push_back(new ImageObj(playText));
	/////////////////////////////////

	// Quit Button//////////////////
	transform = { 300, 300, 50, 25 };

	UIButton* pQuitButton = new UIButton(transform, buttonDisp, buttonHighlightDisp);
	pQuitButton->SetCallback(QuitGame(pOwner));

	Display quitText("Quit", 100, SDL_Color{ 255, 255, 255, 255 }, SDL_Rect{ 300, 300, 50, 25 });

	m_displayList.push_back(pQuitButton);
	m_displayList.push_back(new ImageObj(quitText));
	///////////////////////////////////

	m_buttonSet.push_back(pPlayButton);
	m_buttonSet.push_back(pQuitButton);

}

MainMenu::~MainMenu()
{
	Deinitialize();
}

void MainMenu::Deinitialize()
{
	for (int i = 0; i < m_displayList.size(); ++i)
	{
		delete m_displayList[i];
	}

	m_displayList.clear();
	m_buttonSet.clear();
}

void MainMenu::Render(SDLWrap& renderer) const
{
	// Clear.
	renderer.ClearDisplayList();

	// Draw.
	for (int i = 0; i < m_displayList.size(); ++i)
	{
		renderer.AddToDisplay(m_displayList[i]->GetDisplay());
	}

	// render
	renderer.Draw();
}

////////////////////////////////////////////
// changes state in state machine to gameplay 
// returns true to quit
////////////////////////////////////////////
bool MainMenu::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_WINDOWEVENT:
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;	
		break;
	}

	for (int i = 0; i < m_buttonSet.size(); ++i)
	{
		m_buttonSet[i]->HandleEvent(pEvent);
	}

	return false;
}
