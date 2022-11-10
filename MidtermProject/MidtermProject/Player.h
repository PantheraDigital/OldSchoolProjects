#pragma once
#include <conio.h>

#include "Vec2D.h"




class Player
{
	const char m_icon;//displayed char

	int m_x, m_y;//coordinates
	int m_keys;
	int m_lives;

public:

	Player();
	~Player();

	void SetPosition(int x, int y);
	void SetPosition(Vec2D coord);
	Vec2D GetPosition();

	void AddKey() { ++m_keys; }
	void SubtractKey() { --m_keys; }
	int GetKeys() { return m_keys; }

	int GetLives() { return m_lives; }
	void SubLife() { --m_lives; }

	Vec2D Input();//reurns desired location
};
