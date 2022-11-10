#include "EventManeger.h"



EventManeger::EventManeger()
{
}


EventManeger::~EventManeger()
{
}

void EventManeger::RegisterCallback(Callback callback)
{
	m_callbackList.push_back(callback);
}

void EventManeger::TriggerCallbacks()
{
	for (auto c : m_callbackList)
	{
		c();
	}
}