#pragma once
#include "GameStateMachine.h"

class GameState;
class Game;

/////////////////////////////////////////////
// State machine for game states
/////////////////////////////////////////////
class GameplayStateMachine : public GameStateMachine
{
	Game* m_pOwner;

	GameState* m_pCurrentState;
	GameState* m_pNextState;

public:
	enum class SceneName
	{
		kMainMenu
		,kGameplay
		,kGameOver
	};


	GameplayStateMachine(Game* pOwner);
	~GameplayStateMachine();

	//Initialize state machine/ returns true if successful
	bool Initialize() override;

	void UpdateCurrentState(double deltaTime) override;

	void RenderCurrentState(SDLWrap& renderer) const override;

	bool HandleEvent(SDL_Event* pEvent) override;

	void ChangeState(GameState* pNewState) override;

	void LoadScene(SceneName scene);

	Game* GetGame() { return m_pOwner; }

	bool Deinitialize() override;
};