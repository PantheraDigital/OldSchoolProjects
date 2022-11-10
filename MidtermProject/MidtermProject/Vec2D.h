#pragma once

struct Vec2D
{
	int m_x;
	int m_y;

	friend bool operator==(const Vec2D &left, const Vec2D &right)
	{
		return left.m_x == right.m_x && left.m_y == right.m_y;
	}


};
