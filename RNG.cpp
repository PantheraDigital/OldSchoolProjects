#include "RNG.h"

RNG::RNG(int min, int max)
	:m_seed(m_randDev())
{
	SetSeed(m_seed);

	if (min > max)
		m_range = std::uniform_int_distribution<int>(max, min);
	else
		m_range = std::uniform_int_distribution<int>(min, max);
}

RNG::RNG(int min, int max, unsigned int seed)
	:RNG(min, max)
{
	SetSeed(seed);
}

RNG::~RNG()
{}


void RNG::SetSeed(unsigned int seed)
{
	m_engine.seed(seed);
}

void RNG::SetRange(int min, int max)
{
	int minimum = min;
	int maximum = max;

	if (minimum > maximum)
	{
		int temp = minimum;
		minimum = maximum;
		maximum = temp;
	}

	if (minimum == m_range.min() && maximum == m_range.max())
		return;

	m_range = std::uniform_int_distribution<int>(minimum, maximum);
}

int RNG::Generate()
{
	return (int)m_range(m_engine);
}