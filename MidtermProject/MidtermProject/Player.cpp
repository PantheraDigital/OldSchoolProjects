#include "Player.h"
#include <iostream>

Player::Player()
	:m_icon('P')
	,m_lives(3)
{

}

Player::~Player()
{

}


////////////////////////////////////////
//set m_x and m_y 
///////////////////////////////////
void Player::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
void Player::SetPosition(Vec2D coord)
{
	m_x = coord.m_x;
	m_y = coord.m_y;
}

Vec2D Player::GetPosition()
{
	Vec2D position;
	position.m_x = m_x;
	position.m_y = m_y;
	return position;
}

/////////////////////////////////////////
//take user input and returns new desired location
///////////////////////////////////////
Vec2D Player::Input()
{
	Vec2D coords;
	coords.m_x = m_x;
	coords.m_y = m_y;

	char input = _getch();

	if (input == 'w')
	{
		--coords.m_y;
	}
	else if (input == 'a')
	{
		--coords.m_x;
	}
	else if (input == 's')
	{
		++coords.m_y;
	}
	else if (input == 'd')
	{
		++coords.m_x;
	}

	return coords;
}

