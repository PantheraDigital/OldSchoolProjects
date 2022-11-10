#pragma once
#include <array>

typedef std::array<std::array<char, 10>, 15> Level;


constexpr char g_kAi = 'A';
constexpr char g_kTown = 'T';
constexpr char g_kWall = 'w';

struct LevelLayout
{
	const int m_LevelX = 10;
	const int m_LevelY = 15;

	Level m_level =
	{ {
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" },
		{ "123456789" }
	} };


};
