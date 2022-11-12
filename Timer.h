#pragma once
#include <chrono>
#include <functional>


class Timer
{
public:
	//how update() calls m_callback
	enum class UpdateType
	{
		kPulse
		,kSingle
	};

private:

	std::chrono::high_resolution_clock::time_point m_start;
	double m_delay;
	std::function<void()> m_callback;
	UpdateType m_updateType;

public:

	Timer()
		:m_delay(0)
		, m_callback(nullptr)
		, m_updateType(UpdateType::kSingle)
	{}

	
	void Set(double delay, UpdateType type, std::function<void()> callback)
	{
		m_start = std::chrono::high_resolution_clock::now();
		m_delay = delay;
		m_callback = callback;
		m_updateType = type;
	};

	void Update()
	{
		if (!m_callback)
			return;

		//update time
		std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_start;

		if (duration.count() >= m_delay)
		{
			switch (m_updateType)
			{

			case Timer::UpdateType::kPulse:
			{
				m_start = std::chrono::high_resolution_clock::now();
				m_callback();
				break;
			}

			case Timer::UpdateType::kSingle:
			{
				m_callback();
				break;
			}

			default:
				break;
			}
		}
	};


};