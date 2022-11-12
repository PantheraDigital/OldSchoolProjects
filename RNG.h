#pragma once
#include <random>

class RNG
{
	std::mt19937 m_engine;
	std::random_device m_randDev;

	unsigned int m_seed;
	std::uniform_int_distribution<int> m_range;

public:
	RNG(int min, int max);
	RNG(int min, int max, unsigned int seed);

	~RNG();


	void SetSeed(unsigned int seed);

	void SetRange(int min, int max);

	std::uniform_int_distribution<int> GetRange() { return m_range; }

	int Generate();
};