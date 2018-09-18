#include "ComponentManager.h"

#include "Component.h"
#include "ObjectManager.h"

//-----------------------------------------------------------

CComponentManager::CComponentManager()
{
}

//-----------------------------------------------------------

CComponent& CComponentManager::CreateComponent(const CComponent& aComponentToAdd, unsigned int aGameObjectID, void* aComponentCreationParams)
{
	const SRawComponentData& componentData = aComponentToAdd.GetRawData();

	char* createdComponentMemory = new char[componentData.mySizeof];
	memcpy(createdComponentMemory, componentData.myAddress, componentData.mySizeof);
	
	CComponent* asComponent = reinterpret_cast<CComponent*>(createdComponentMemory);
	myObjectToComponentListLUT[aGameObjectID].push_back(asComponent);

	asComponent->OnCreated(aComponentCreationParams);

	return *asComponent;
}

//-----------------------------------------------------------

void CComponentManager::OnStart()
{
	for (auto& componentList : myObjectToComponentListLUT)
	{
		for (auto& component : componentList.second)
		{
			component->OnStart();
		}
	}
}

//-----------------------------------------------------------

void CComponentManager::TickComponentsForObject(unsigned int aGameObjectID, float aDT)
{
	for (auto*& component : myObjectToComponentListLUT[aGameObjectID])
	{
		if (!component->ShouldTick())
		{
			continue;
		}

		component->Tick(aDT); 
	}
}

//-----------------------------------------------------------
