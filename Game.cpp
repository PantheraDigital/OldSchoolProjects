#include "Game.h"

#include "GameStateMachine.h"
#include "DeltaClock.h"
#include <iostream>

Game::Game()
	: m_colManager()
	, m_pStateMachine(nullptr)
	, m_earlyQuit(false)
{

}

Game::~Game()
{
}

//////////////////////////////////////////
//prepare state machine and renderer
////////////////////////////////////////////
int Game::Initialize(GameStateMachine* pStateMachine)
{
	m_renderer.Initialize();

	// Initialize state machine.
	if (pStateMachine != nullptr && pStateMachine->Initialize())
	{
		
		std::cout << "State machine succeeded." << std::endl;
		m_pStateMachine = pStateMachine;
	}
	else
	{
		std::cout << "Failed to create state machine." << std::endl;
		m_renderer.Deinitialize();
		system("pause");
		return -1;
	}

	return 0;
}

//////////////////////////////////////
//Update states
///////////////////////////////////////
void Game::RunGameLoop()
{
	bool quit = false;
	DeltaClock clock;


	while (!quit)
	{
		clock.Tick();
		double deltaTime = clock.GetDeltaTime();

		quit = ProcessEvents();
		m_pStateMachine->UpdateCurrentState(deltaTime);
		m_pStateMachine->RenderCurrentState(m_renderer);

		if (m_earlyQuit)
			quit = true;
	}
}

//////////////////////////////////////////
//Deinitialize state machine and renderer
//////////////////////////////////////
void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Deinitialize();

	m_renderer.Deinitialize();
}

//////////////////////////////////////
//checks for quit
//////////////////////////////////////////
bool Game::ProcessEvents()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		bool quit = m_pStateMachine->HandleEvent(&evt);

		if (quit)
			return true;
	}
	return false;
}
