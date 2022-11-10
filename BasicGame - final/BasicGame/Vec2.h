#pragma once

//storage for a set of ints
struct Vec2
{
public:
	int m_x, m_y;

	Vec2()
		:m_x(-1)
		, m_y(-1)
	{}

	Vec2(int x, int y)
		:m_x(x)
		, m_y(y)
	{}

	Vec2(const Vec2& copy)
	{
		*this = copy;
	}


	bool operator==(const Vec2& right) const
	{
		return ((m_x == right.m_x) && (m_y == right.m_y));
	}

	bool operator<(const Vec2& right) const
	{
		if (m_y < right.m_y)
			return true;

		return m_x < right.m_x;
	}

	bool operator>(const Vec2& right) const
	{
		return right < *this;
	}

	bool operator>=(const Vec2& right) const
	{
		return !(*this < right);
	}

	bool operator<=(const Vec2& right) const
	{
		return !(*this > right);
	}


	Vec2 operator+(const Vec2& right)
	{
		return Vec2((m_x + right.m_x), (m_y + right.m_y));
	}

	Vec2& operator+=(const Vec2& right)
	{
		m_x += right.m_x;
		m_y += right.m_y;
		return *this;
	}

	Vec2& operator=(const Vec2& right)
	{
		m_x = right.m_x;
		m_y = right.m_y;
		return *this;
	}

};

class Vec2MapSort
{
public:
	bool operator()(const Vec2& left, const Vec2& right) const
	{
		if (left.m_y < right.m_y)
			return true;

		if (left.m_y == right.m_y)
		{
			if (left.m_x < right.m_x)
				return true;
		}

		return false;
	}
};