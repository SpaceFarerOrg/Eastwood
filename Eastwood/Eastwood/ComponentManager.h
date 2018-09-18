#pragma once
#include "Component.h"
#include <unordered_map>
#include <vector>

class CObjectManager;
class CGameObject;

class CComponentManager
{
public:
	CComponentManager();

	CComponent& CreateComponent(const CComponent& aComponentToAdd, unsigned int aGameObjectID, void* aComponentCreationParams);

	void OnStart();
	void TickComponentsForObject(unsigned int aGameObjectID, float aDT);
private:
	std::unordered_map<unsigned int, std::vector<CComponent*>> myObjectToComponentListLUT;

};