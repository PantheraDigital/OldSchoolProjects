#pragma once

struct Vec2d
{
	int m_x;
	int m_y;

	Vec2d()
		:m_x(0)
		,m_y(0)
	{}
	Vec2d(int x, int y)
		:m_x(x)
		, m_y(y)
	{}
	Vec2d(const Vec2d& vec)
	{
		m_x = vec.m_x;
		m_y = vec.m_y;
	}
	Vec2d(const Vec2d* vec)
	{
		*this = vec;
	}

	friend Vec2d operator+(const Vec2d left, const Vec2d& right)
	{
		Vec2d result(left.m_x + right.m_x, left.m_y + right.m_y);
		return result;
	}
	friend Vec2d operator-(const Vec2d left, const Vec2d& right)
	{
		Vec2d result(left.m_x - right.m_x, left.m_y - right.m_y);
		return result;
	}

	Vec2d& operator=(const Vec2d &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;

		return *this;
	}
	Vec2d& operator=(const Vec2d* other)
	{
		m_x = other->m_x;
		m_y = other->m_y;

		return *this;
	}

	Vec2d& operator+=(const Vec2d &other)
	{
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}
	Vec2d* operator+=(const Vec2d* other)
	{
		m_x += other->m_x;
		m_y += other->m_y;
		return this;
	}

	friend bool operator==(const Vec2d &left, const Vec2d &right)
	{
		return (left.m_x == right.m_x && left.m_y == right.m_y);
	}
	friend bool operator!=(const Vec2d &left, const Vec2d &right)
	{
		return !(left.m_x == right.m_x && left.m_y == right.m_y);
	}

	friend bool operator<(const Vec2d& l, const Vec2d& r)
	{
		return (l.m_x < r.m_x && l.m_y < r.m_y);
	}
	friend bool operator>(const Vec2d& l, const Vec2d& r)
	{
		return r < l;
	}

};