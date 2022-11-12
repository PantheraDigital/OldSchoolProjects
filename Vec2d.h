#pragma once
#include <cmath>


template<typename Type>
struct Vec2d
{
	Type m_x, m_y;

	Vec2d()
		:m_x(NULL)
		, m_y(NULL)
	{}

	Vec2d(Type x, Type y)
		:m_x(x)
		, m_y(y)
	{}

	Vec2d(const Vec2d<Type>& copy)
		:m_x(copy.m_x)
		, m_y(copy.m_y)
	{}


	//scalar
	friend Vec2d operator*(const Vec2d<Type>& lhs, const Type& rhs)
	{
		Vec2d<Type> result(lhs.m_x * rhs, lhs.m_y * rhs);
		return result;
	}
	//dot
	friend double operator*(const Vec2d<Type>& lhs, const Vec2d<Type>& rhs)
	{
		return (lhs.m_x * rhs.m_x) + (lhs.m_y * rhs.m_y);
	}

	friend Vec2d operator+(const Vec2d<Type>& lhs, const Vec2d<Type>& rhs)
	{
		Vec2d<Type> result(lhs.m_x * rhs.m_x, lhs.m_y * rhs.m_y);
		return result;
	}

	friend Vec2d operator-(const Vec2d<Type>& lhs, const Vec2d<Type>& rhs)
	{
		Vec2d<Type> result(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
		return result;
	}

	Vec2d<Type>& operator=(const Vec2d<Type>& rhs)
	{
		m_x = rhs.m_x;
		m_y = rhs.m_y;

		return *this;
	}

	Vec2d<Type>& operator+=(const Vec2d<Type>& rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		return *this;
	}

	//scalar
	Vec2d<Type>& operator*=(const Type& rhs)
	{
		m_x *= rhs;
		m_y *= rhs;
		return *this;
	}

	Vec2d<Type>& operator*=(const Vec2d<Type>& rhs)
	{
		m_x *= rhs.m_x;
		m_y *= rhs.m_y;
		return *this;
	}

	float GetMagnitude()
	{
		return sqrt((m_x * m_x) + (m_y * m_y));
	}

	float GetSquaredMagnitude()
	{
		return (m_x * m_x) + (m_y * m_y);
	}

	float Distance(Vec2d<Type> rhs)
	{
		float x = rhs.m_x - m_x;
		float y = rhs.m_y + m_y;

		return sqrt((x * x) + (y * y));
	}

	float DistanceSquared(Vec2d<Type> rhs)
	{
		float x = rhs.m_x - m_x;
		float y = rhs.m_y + m_y;

		return (x * x) + (y * y);
	}

	float SquaredDistance(Vec2d<Type> rhs)
	{
		float x = rhs.m_x - m_x;
		float y = rhs.m_y + m_y;

		return (x * x) + (y * y);
	}

	Vec2d<Type> GetNorm()
	{
		float mag = GetMagnitude();
		Vec2d<Type> result;
		result.m_x = m_x / mag;
		result.m_y = m_y / mag;

		return result;
	}
};