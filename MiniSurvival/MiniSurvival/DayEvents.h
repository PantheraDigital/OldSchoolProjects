#pragma once
#include <string>
#include <vector>

class DayEvents
{
	std::vector<std::string> m_events;
	int RandPick();
	
public:
	DayEvents();
	~DayEvents();

	std::string GetEvent();
};

