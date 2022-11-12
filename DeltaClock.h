#pragma once
#include <chrono>


//stores time between Ticks 
class DeltaClock
{
	std::chrono::high_resolution_clock::time_point m_lastFrame;
	double m_delta;

public:
	DeltaClock()
		:m_lastFrame(std::chrono::high_resolution_clock::now())
		,m_delta(0)
	{}

	void Tick();
	double GetDeltaTime();
	double GetDeltaAdjust(float percent);
};