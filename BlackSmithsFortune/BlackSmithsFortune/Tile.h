#pragma once





struct Tile
{
	char m_face;
	bool m_blockPlayer;

	Tile(char face, bool block)
		:m_face(face)
		,m_blockPlayer(block)
	{}
};

