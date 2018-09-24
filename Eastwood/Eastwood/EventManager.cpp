#include "EventManager.h"

CEventManager & CEventManager::GetInstance()
{
	static CEventManager instance;

	return instance;
}

void CEventManager::SubscribeToEvent(const std::string & aEventName, std::function<void(const SEventData&)> aFunctionToSubscribeWith)
{
	mySubscribers[aEventName].push_back(aFunctionToSubscribeWith);
}

void CEventManager::FireEvent(const std::string& aEventName, const SEventData & aEventData)
{
	auto& subscribersToEvent = mySubscribers[aEventName];

	for (auto& subscriber : subscribersToEvent)
	{
		subscriber(aEventData);
	}
}
