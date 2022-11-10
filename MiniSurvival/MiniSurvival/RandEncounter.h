#pragma once
#include <string>
#include <vector>

struct Encounters
{
	std::string m_words;
	int m_damage;
	int m_maxRewards;
	int m_energyLv;

	Encounters(std::string words, int dam, int reward, int lv)
		:m_words(words),
		m_damage(dam),
		m_maxRewards(reward),
		m_energyLv(lv)
	{};

	Encounters() {};
};


class RandEncounter
{
	std::vector<Encounters> m_encounter;
	int RandPick() 
	{
		return (rand() % m_encounter.size());
	}

public:
	RandEncounter();
	~RandEncounter();

	Encounters GetEncounter()
	{
		return m_encounter[RandPick()];
	}

	bool RandEncountCheck();
};

