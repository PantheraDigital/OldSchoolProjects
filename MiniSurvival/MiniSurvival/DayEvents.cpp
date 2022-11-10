#include "DayEvents.h"

DayEvents::DayEvents()
{
	m_events.push_back("While you're out you find some goods in a run down building: ");
	m_events.push_back("On your journy you find: ");
	m_events.push_back("Walking back you run into a garbedg can with: ");
	m_events.push_back("Looking through abandoned cars you find: ");
	m_events.push_back("Going through abandoned hoses you come accross: ");
}


DayEvents::~DayEvents()
{
}

////////////////////////
//returns string of random index from vector
////////////////////////
std::string DayEvents::GetEvent()
{
	return m_events[RandPick()];
}

////////////////////////
//gives random num based on vector size
////////////////////////
int DayEvents::RandPick()
{
	return (rand() % m_events.size());
}
