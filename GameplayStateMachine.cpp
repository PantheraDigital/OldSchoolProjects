#include "GameplayStateMachine.h"

#include "Game.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "GameOver.h"


GameplayStateMachine::GameplayStateMachine(Game* pOwner)
	: m_pOwner(pOwner)
	, m_pCurrentState(nullptr)
	, m_pNextState(nullptr)
{
}

GameplayStateMachine::~GameplayStateMachine()
{
}


//////////////////////////////
//load firts state/ return true if successful
///////////////////////////////////
bool GameplayStateMachine::Initialize()
{
	LoadScene(SceneName::kMainMenu);
	return true;
}

/////////////////////////////////
//updates and changes state
////////////////////////////////////
void GameplayStateMachine::UpdateCurrentState(double deltaTime)
{
	//change
	if (m_pNextState != nullptr)
	{
		ChangeState(m_pNextState);
		m_pNextState = nullptr;
	}

	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(deltaTime);
	}
}


void GameplayStateMachine::RenderCurrentState(SDLWrap& renderer) const
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Render(renderer);
	}
}

/////////////////////////////////////////////
// checks for quit
/////////////////////////////////////////////
bool GameplayStateMachine::HandleEvent(SDL_Event* pEvent)
{
	if (m_pCurrentState == nullptr)
	{
		return false;
	}
	else
	{
		return m_pCurrentState->HandleEvent(pEvent);
	}
}

void GameplayStateMachine::ChangeState(GameState* pNewState)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	delete m_pCurrentState;
	m_pCurrentState = pNewState;
	pNewState->Enter();
}

void GameplayStateMachine::LoadScene(SceneName scene)
{
	switch (scene)
	{
	case SceneName::kMainMenu:
		m_pNextState = new MainMenu(this);
		break;
	case SceneName::kGameplay:
		m_pNextState = new GamePlay(this);
		break;
	case SceneName::kGameOver:
		m_pNextState = new GameOver(this);
		break;
	}

}

bool GameplayStateMachine::Deinitialize()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
		delete m_pCurrentState;
	}

	return true;
}