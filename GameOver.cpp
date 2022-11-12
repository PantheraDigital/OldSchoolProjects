#include "GameOver.h"

#include "GameplayStateMachine.h"
#include "Game.h"
#include "ImageLoader.h"
#include "ImageObj.h"

#include "ButtonFunctions.h"


GameOver::GameOver(GameplayStateMachine* pOwner)
	: m_pOwner(pOwner)
{
	m_displayList.push_back(new ImageObj(Display(ImageLoader::GetInst()->GetImage("PHGameover"), false)));

	//replay button///////////
	SDL_Rect transform{ 200, 350, 50, 30 };
	Display buttonDisp(transform, SDL_Color{ 64, 64, 64, SDL_ALPHA_OPAQUE });
	Display buttonHighlightDisp(transform, SDL_Color{ 128, 128, 128, SDL_ALPHA_OPAQUE });

	UIButton* pReplayButton = new UIButton(transform, buttonDisp, buttonHighlightDisp);
	pReplayButton->SetCallback(GameplayStateChange(pOwner, GameplayStateMachine::SceneName::kGameplay));

	Display playText("Replay", 100, SDL_Color{ 255, 255, 255, 255 }, transform);

	m_displayList.push_back(pReplayButton);
	m_displayList.push_back(new ImageObj(playText));
	/////////////////////////

	//menu button//////////////////////
	transform = { 400, 350, 50, 30 };

	UIButton* pMenuButton = new UIButton(transform, buttonDisp, buttonHighlightDisp);
	pMenuButton->SetCallback(GameplayStateChange(pOwner, GameplayStateMachine::SceneName::kMainMenu));

	Display menuText("Main Menu", 100, SDL_Color{ 255, 255, 255, 255 }, transform);

	m_displayList.push_back(pMenuButton);
	m_displayList.push_back(new ImageObj(menuText));
	//////////////////////////////////

	m_buttonSet.push_back(pReplayButton);
	m_buttonSet.push_back(pMenuButton);
}

GameOver::~GameOver()
{
	for (int i = 0; i < m_displayList.size(); ++i)
	{
		delete m_displayList[i];
	}
}


void GameOver::Render(SDLWrap& renderer) const
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
bool GameOver::HandleEvent(SDL_Event* pEvent)
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