#pragma once
#include <vector>


typedef void(*Callback)();

class EventManeger
{
	std::vector<Callback> m_callbackList;

public:
	EventManeger();
	~EventManeger();

	void RegisterCallback(Callback callback);
	void TriggerCallbacks();
};


