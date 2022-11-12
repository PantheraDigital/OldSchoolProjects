#pragma once

#include "Pawn.h"
#include "ColComp.h"
#include "RNG.h"
#include <iostream>

class KillPlayer
{
	Pawn* m_pPlayer;

public:

	KillPlayer(Pawn* player)
		:m_pPlayer(player)
	{}

	~KillPlayer()
	{
		m_pPlayer = nullptr;
	}


	void operator() (ColComp* col)
	{
		m_pPlayer->Kill();
	}
};


class PlayerSpeedBoost
{
	Pawn* m_pPlayer;
public:
	PlayerSpeedBoost(Pawn* player)
		:m_pPlayer(player)
	{}

	~PlayerSpeedBoost()
	{
		m_pPlayer = nullptr;
	}


	void operator() (ColComp* col)
	{
		m_pPlayer->SetSpeedMod(2.0f);
	}
};


class RandomChance
{
	Pawn* m_pPlayer;

	bool m_used;
public:
	RandomChance(Pawn* player)
		:m_pPlayer(player)
		,m_used(false)
	{}

	~RandomChance()
	{
		m_pPlayer = nullptr;
	}


	void operator() (ColComp* col)
	{
		if (m_used)
			return;

		RNG m_rng(1,50);
		int temp = m_rng.Generate();

		std::cout << temp << std::endl;
		if ((temp % 2) == 0)
			m_pPlayer->SetSpeedMod(2.0f);
		else
			m_pPlayer->Kill();

		m_used = true;
	}
};