#include "GamePlay.h"

#include "GameplayStateMachine.h"
#include "Game.h"
#include "Object.h"
#include "LevelLoader.h"


GamePlay::GamePlay(GameplayStateMachine* pOwner)
	: m_pOwner(pOwner)
	, m_pPlayer(nullptr)
	, m_layout()
{
	m_pOwner->GetGame()->GetRenderer().GetDisplaySize(m_camera.w, m_camera.h);
	m_camera.w -= 400;
	m_camera.h -= 300;
}

GamePlay::~GamePlay()
{
}


void GamePlay::Enter()
{
	m_pPlayer = new Pawn(m_pOwner->GetGame()->GetColManager());
	m_pPlayer->SetSpawn(Vec2d<int>(100, 100));
	m_pPlayer->SetPos(Vec2d<int>(100, 100));
	LevelLoader::Load(m_layout, 0, m_pOwner->GetGame()->GetColManager(), m_pPlayer);
}

void GamePlay::Update(double deltaTime)
{
	m_layout.Update(deltaTime);
	m_pPlayer->Update(deltaTime);

	m_camera = m_pPlayer->GetDisplay().GetTransform();

	m_pOwner->GetGame()->GetRenderer().UpdateCamera(m_camera);
}

void GamePlay::Render(SDLWrap& renderer) const 
{
	// Clear.
	renderer.ClearDisplayList();

	// Draw.
	m_layout.Render(renderer);
	m_pPlayer->Render(renderer);


	//render coll////////////////////////////
	renderer.AddToDisplay(m_pOwner->GetGame()->GetColManager()->GetCollisions(), 2);

	// render
	renderer.Draw();

}

///////////////////////////////////////
// returns true when quit
///////////////////////////////////////
bool GamePlay::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_WINDOWEVENT:
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;
		break;

	}

	return false;
}

void GamePlay::Exit()
{
}
