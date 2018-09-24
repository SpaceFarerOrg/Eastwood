#pragma once
#include <unordered_map>
#include <vector>
#include <functional>

union Value
{
	int myInt;
	float myFloat;
};

struct SEventData
{
	std::unordered_map<std::string, Value> myDataBlackboard;
};

class CEventManager
{
public:
	static CEventManager& GetInstance();

	void SubscribeToEvent(const std::string& aEventName, std::function<void(const SEventData&)> aFunctionToSubscribeWith);
	void FireEvent(const std::string& aEventName, const SEventData& aEventData);

private:
	CEventManager();

	std::unordered_map<std::string, std::vector<std::function<void(const SEventData&)>>> mySubscribers;
};