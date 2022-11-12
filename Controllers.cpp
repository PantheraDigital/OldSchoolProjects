#include "Controllers.h"



PlayerController::PlayerController()
	:m_pKeystates(SDL_GetKeyboardState(NULL))
	//, m_input()
{}

////////////////////////////////////////////
//will return a normalized vec to be used by pawn to determin move direction
/////////////////////////////////////////////////////////////
Vec2d<float> PlayerController::GetDirection()
{
	if (m_pKeystates[SDL_SCANCODE_W])
		m_direction.m_y = -1;

	if (m_pKeystates[SDL_SCANCODE_S])
		m_direction.m_y = 1;

	if (!m_pKeystates[SDL_SCANCODE_W] && !m_pKeystates[SDL_SCANCODE_S])
		m_direction.m_y = 0;


	if (m_pKeystates[SDL_SCANCODE_A])
		m_direction.m_x = -1;

	if (m_pKeystates[SDL_SCANCODE_D])
		m_direction.m_x = 1;

	if (!m_pKeystates[SDL_SCANCODE_A] && !m_pKeystates[SDL_SCANCODE_D])
		m_direction.m_x = 0;


	return m_direction;
}

bool PlayerController::ShiftDown()
{
	static bool lock = false;

	if (m_pKeystates[SDL_SCANCODE_LSHIFT])
	{
		if (!lock)
		{
			lock = true;

		}	
		//unlocked right now
		return true;
	}

	if (!m_pKeystates[SDL_SCANCODE_LSHIFT])
		lock = false;

	return false;
}