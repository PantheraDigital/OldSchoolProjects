#pragma once

class SDLWrap;
struct SDL_Renderer;
union SDL_Event;


//////////////////////////////////
// A game state interface.
//////////////////////////////////
class GameState
{
public:
	virtual ~GameState() {}

	// Initialize
	virtual void Enter() {}

	virtual void Update(double deltaTime) {}

	virtual void Render(SDLWrap& renderer) const = 0;

	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) = 0;

	virtual void Exit() {}
};

