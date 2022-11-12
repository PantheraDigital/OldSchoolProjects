#include "DeltaClock.h"

//////////////////////////////////
//record time since last tick and set curent time
//////////////////////////////////
void DeltaClock::Tick()
{
	auto thisFrameTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> lastFrameDuration = thisFrameTime - m_lastFrame;
	m_delta = lastFrameDuration.count();
	m_lastFrame = thisFrameTime;
}

double DeltaClock::GetDeltaTime()
{
	return m_delta;
}

double DeltaClock::GetDeltaAdjust(float percent)
{
	return m_delta * percent;
}