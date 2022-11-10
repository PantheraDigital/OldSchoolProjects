#pragma once
#include <iostream>

template<typename T>
union VecUnion
{
	T m_var[3];
	struct 
	{
		T m_x;
		T m_y;
		T m_z;
	};
};




template<typename T>
class Vec3
{
	VecUnion<T> m_u;


public:
	Vec3(T x, T y, T z)
	{
		m_u.m_x = x;
		m_u.m_y = y;
		m_u.m_z = z;
	}

	Vec3()
	{
		m_u = 0;
	}

	Vec3(const Vec3& copy)
	{
		*this = copy;
	}

	~Vec3() {}

	const T GetLengthSqrt() const
	{
		T result = NULL;
		for (int i = 0; i < 3; ++i)
			result += (m_u.m_var[i] * m_u.m_var[i]);

		return result;
	}


	//+
	friend Vec3 operator+(const Vec3 &a, const Vec3 &b)
	{
		Vec3 result((a.m_u.m_x + b.m_u.m_x), (a.m_u.m_y + b.m_u.m_y), (a.m_u.m_z + b.m_u.m_z));
		return result;
	}

	//-
	friend Vec3 operator-(const Vec3 &a, const Vec3 &b)
	{
		Vec3 result((a.m_u.m_x - b.m_u.m_x), (a.m_u.m_y - b.m_u.m_y), (a.m_u.m_z - b.m_u.m_z));
		return result;
	}

	//vec * float
	friend Vec3 operator*(const Vec3 &a, T b)
	{
		Vec3 result((a.m_u.m_x * b), (a.m_u.m_y * b), (a.m_u.m_z * b));
		return result;
	}

	//flaot * vec
	friend Vec3 operator*(T a, const Vec3 &b)
	{
		Vec3 result((a * b.m_u.m_x), (a * b.m_u.m_y), (a * b.m_u.m_z));
		return result;
	}

	//vec += vec
	Vec3& operator+=(const Vec3 &b)
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] += b.m_u.m_var[i];
		
		return *this;
	}

	//vec -= vec
	Vec3& operator-=(const Vec3 &b) 
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] -= b.m_u.m_var[i];
		
		return *this;
	}

	//vec *= float
	Vec3& operator*=(const T b)
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] *= b;

		return *this;
	}

	Vec3& operator*=(const float b)
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] *= (int)b;

		return *this;
	}

	//vec /= float
	Vec3& operator/=(const T b)
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] /= b;
		
		return *this;
	}

	Vec3& operator/=(const float b)
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] /= (int)b;

		return *this;
	}

	//vec * vec returns dot(float)
	friend float operator*(const Vec3 &a, const Vec3 &b)
	{
		float result = NULL;
		for (int i = 0; i < 3; ++i)
			result += (float)(a.m_u.m_var[i] * b.m_u.m_var[i]);

		return result;
	}

	//vec / vec returns cross(vec)
	friend Vec3 operator/(const Vec3 &a, const Vec3 &b)
	{
		Vec3 result = (((a.m_u.m_y * b.m_u.m_z) - (a.m_u.m_z * b.m_u.m_y)), ((a.m_u.m_z * b.m_u.m_x) - (a.m_u.m_x * b.m_u.m_z)), ((a.m_u.m_x * b.m_u.m_y) - (a.m_u.m_y * b.m_u.m_z)));
		return result;
	}

	//<<
	friend std::ostream& operator<<(std::ostream& os, const Vec3& obj)
	{
		os << obj.m_u.m_x << ", " << obj.m_u.m_y << ", " << obj.m_u.m_z;
		return os;
	}


	//part two

	//cin/ >> 
	friend std::istream& operator>>(std::istream& is, const Vec3& obj)
	{
		is >> obj.m_u.m_x >> obj.m_u.m_y >> obj.m_u.m_z;
		return is;
	}

	//==
	friend bool operator==(const Vec3 &a, const Vec3&b)
	{
		return (a.m_u.m_x == b.m_u.m_x && a.m_u.m_y == b.m_u.m_y && a.m_u.m_z == b.m_u.m_z);
	}

	//!=
	friend bool operator!=(const Vec3 &a, const Vec3&b)
	{
		return !(a == b);
	}

	//>
	friend bool operator>(const Vec3 &a, const Vec3&b)
	{
		return b < a;
	}

	//<
	friend bool operator<(const Vec3 &a, const Vec3 &b)
	{
		return a.GetLengthSqrt() < b.GetLengthSqrt();
	}

	// >=
	friend bool operator>=(const Vec3 &a, const Vec3&b)
	{
		return !(a < b);
	}

	//<=
	friend bool operator<=(const Vec3 &a, const Vec3&b)
	{
		return !(a > b);
	}

	//[]/array access
	T& operator[](std::size_t idx)//1 gives x/ 2 gives y/ anything else gives z
	{
		return m_u.m_var[idx];
	}
	const T& operator[](std::size_t idx) const
	{
		return m_u.m_var[idx];
	}

	//=
	Vec3& operator=(const Vec3 &other) ////////assignment oparator 
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] = other.m_u.m_var[i];

		return *this;
	}

	Vec3& operator=(T other) ////////assignment oparator 
	{
		for (int i = 0; i < 3; ++i)
			m_u.m_var[i] = other;

		return *this;
	}



};

