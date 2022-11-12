#pragma once
#include <vector>

#include "GameState.h"
#include "Pawn.h"
#include "Layout.h"

class Object;
class GameplayStateMachine;


////////////////////////////////
//game state in charge of game play
///////////////////////////////////
class GamePlay : public GameState
{
private:
	GameplayStateMachine* m_pOwner;

	Pawn* m_pPlayer;

	Layout m_layout;

	//will be the area on screen that the player can move in
	SDL_Rect m_camera;

public:
	GamePlay(GameplayStateMachine* pOwner);
	~GamePlay();

	void Enter() override;

	void Update(double deltaTime) override;

	void Render(SDLWrap& renderer) const override;

	bool HandleEvent(SDL_Event* pEvent) override;

	void Exit() override;
};



