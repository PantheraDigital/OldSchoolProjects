#pragma once

#include "ColManager.h"
#include "Object.h"
#include "SDLWrap.h"

class GameStateMachine;

///////////////////////////////////
//contains and manages game states uising state machine
//also runs the main loop updating the game
//////////////////////////////////////////
class Game
{
	//class used for rendering
	SDLWrap m_renderer;
	//class in charge of collision
	ColManager m_colManager;
	
	GameStateMachine* m_pStateMachine;

	bool m_earlyQuit;

	bool ProcessEvents();

public:

	Game();
	~Game();

	int Initialize(GameStateMachine* pStateMachine);

	void RunGameLoop();

	void Deinitialize();

	SDLWrap& GetRenderer() { return m_renderer; }

	ColManager* GetColManager() { return &m_colManager; }

	void Quit() { m_earlyQuit = true; }
};
