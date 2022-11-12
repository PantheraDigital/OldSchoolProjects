#pragma once

class SDLWrap;
class GameState;
union SDL_Event;

/////////////////////////////////////////////////////
//interface for state machines that handel game states
/////////////////////////////////////////////////////
class GameStateMachine
{
public:
	virtual ~GameStateMachine() {}

	// Initializes this state machine.
	// Returns false if any errors occur.
	virtual bool Initialize() = 0;

	// Updates the currently active scene.
	virtual void UpdateCurrentState(double deltaTime) = 0;

	// Renders the currently active scene.
	virtual void RenderCurrentState(SDLWrap& renderer) const  = 0;

	// Handles the given event.
	// Returns true when it's time to quit.
	virtual bool HandleEvent(SDL_Event* pEvent) = 0;

	// Exits current state and enters new state.
	virtual void ChangeState(GameState* pNewState) = 0;

	// Cleans up this state machine.
	// Returns false if any errors occur.
	virtual bool Deinitialize() = 0;
};