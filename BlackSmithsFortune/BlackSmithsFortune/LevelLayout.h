#pragma once
#include <array>
typedef std::array<std::array<char, 45>, 15> Level;

//character key for tiles used
constexpr char g_kPlayer = 'P';
constexpr char g_kAi = 'A';
constexpr char g_kTown = 'T';
constexpr char g_kWall = 'w';
constexpr char g_kGround = ' ';

struct LevelLayout
{
	//map dimensions
	const int m_LevelX = 45;
	const int m_LevelY = 15;

	Level m_level =
	{ {
		{ "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" },
		{ "w                    ww                    w" },
		{ "w       T              w      T            w" },
		{ "w  P                   w                   w" },
		{ "wwwww                                      w" },
		{ "w      ww                           A      w" },
		{ "w                         wwwww            w" },
		{ "w        ww          w         wwww        w" },
		{ "w  A                w             wwww     w" },
		{ "w                  w                       w" },
		{ "w                 w                        w" },
		{ "w    T          www             T          w" },
		{ "w            www                           w" },
		{ "w                                          w" },
		{ "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww" }
	} };

	std::array<int,4> m_townPop = { 4,7,3,9 };//population of cities from left to right in each row
};
