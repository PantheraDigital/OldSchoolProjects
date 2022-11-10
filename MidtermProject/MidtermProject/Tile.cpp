#include "Tile.h"


/////////////////////////////////////////
//sets internal variables based on given state
/////////////////////////////////////////
void Tile::SetState(State state)
{
	switch (state)
	{
		case State::k_background:
		{
			m_face = ' ';
			m_blockPlayer = false;
			m_killPlayer = false;
			m_state = State::k_background;
			break;
		}
		case State::k_deadly:
		{
			m_face = 'X';
			m_killPlayer = true;
			m_blockPlayer = false;
			m_state = State::k_deadly;
			break;
		}
		case State::k_wall:
		{
			m_face = 'W';
			m_blockPlayer = true;
			m_killPlayer = false;
			m_state = State::k_wall;
			break;
		}
		case State::k_door:
		{
			m_face = 'D';
			m_blockPlayer = true;
			m_killPlayer = false;
			m_state = State::k_door;
			break;
		}
		case State::k_end:
		{
			m_face = 'E';
			m_end = true;
			m_blockPlayer = false;
			m_state = State::k_end;
			break;
		}
	}
}

