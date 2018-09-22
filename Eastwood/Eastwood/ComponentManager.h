#pragma once
#include "Component.h"
#include <unordered_map>
#include <vector>
#include "ComponentRuntimeDataDefines.h"

class CObjectManager;
class CGameObject;

class CComponentManager
{
public:
	CComponentManager();

	CComponent& CreateComponent(const CComponent& aComponentToAdd, unsigned int aGameObjectID, void* aComponentCreationParams);

	void OnStart();
	void TickComponentsForObject(unsigned int aGameObjectID, float aDT);
	void DestroyAllComponentsForObject(unsigned int aGameObjectID);

	CComponent* GetComponent(unsigned int aGameObjectID, ComponentType aComponentType);
private:
	std::unordered_map<unsigned int, std::vector<CComponent*>> myObjectToComponentListLUT;

};