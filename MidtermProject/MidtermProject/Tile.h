#pragma once

class TileFactory;



class Tile
{
	friend TileFactory;

public:

	enum class State
	{
		k_background
		, k_deadly
		, k_wall
		, k_door
		, k_end
	};

	State GetState() { return m_state; }

	char GetFace() { return m_face; }
	bool GetBlockPlayer() { return m_blockPlayer; }
	bool GetKillPlayer() { return m_killPlayer; }
	bool GetEnd() { return m_end; }

	void SetFace(char face) { m_face = face; }

	void SetState(State state);//set variables based on state

private:
	State m_state;
	char m_face;

	bool m_blockPlayer;
	bool m_killPlayer;
	bool m_end;




protected:
	Tile(State state)//used for basic tiles
		:m_blockPlayer(false)
		,m_end(false)
		,m_killPlayer(false)
	{
		SetState(state);
	}

	Tile(char face)//used for keys
		:m_blockPlayer(false)
		, m_end(false)
		, m_killPlayer(false)
	{
		SetState(State::k_background);
		m_face = face;
	}


};