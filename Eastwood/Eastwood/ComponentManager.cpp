#include "ComponentManager.h"

#include "Component.h"
#include "ObjectManager.h"

//-----------------------------------------------------------

CComponentManager::CComponentManager()
{
	myMemoryPool.Initialize(sizeof(CComponent) * 10000);
}

//-----------------------------------------------------------

CComponent& CComponentManager::CreateComponent(const CComponent& aComponentToAdd, unsigned int aGameObjectID, void* aComponentCreationParams)
{
	const SRawComponentData& componentData = aComponentToAdd.GetRawData();

	unsigned int memID = myMemoryPool.AddToPool(componentData.myAddress, componentData.mySizeof);
	
	CComponent* asComponent = reinterpret_cast<CComponent*>(myMemoryPool[memID]);
	
	SComponentHandle addedComponentHandle;
	addedComponentHandle.myComponent = asComponent;
	addedComponentHandle.myMemoryPoolId = memID;

	myObjectToComponentListLUT[aGameObjectID].push_back(addedComponentHandle);

	asComponent->OnCreated(aComponentCreationParams);

	return *asComponent;
}

//-----------------------------------------------------------

void CComponentManager::OnStart()
{
	for (auto& componentList : myObjectToComponentListLUT)
	{
		for (auto& componentHandle : componentList.second)
		{
			componentHandle.myComponent->OnStart();
		}
	}
}

//-----------------------------------------------------------

void CComponentManager::TickComponentsForObject(unsigned int aGameObjectID, float aDT)
{
	for (auto& componentHandle : myObjectToComponentListLUT[aGameObjectID])
	{
		if (!componentHandle.myComponent->ShouldTick())
		{
			continue;
		}

		componentHandle.myComponent->Tick(aDT); 
	}
}

//-----------------------------------------------------------

void CComponentManager::DestroyAllComponentsForObject(unsigned int aGameObjectID)
{
	std::vector<SComponentHandle>& componentList = myObjectToComponentListLUT[aGameObjectID];

	for (SComponentHandle& componentHandle : componentList)
	{
		componentHandle.myComponent->OnDestroy();
		myMemoryPool.RemoveFromPool(componentHandle.myMemoryPoolId, componentHandle.myComponent->GetRawData().mySizeof);
	}
	
	myObjectToComponentListLUT.erase(aGameObjectID);
}

//-----------------------------------------------------------

CComponent* CComponentManager::GetComponent(unsigned int aGameObjectID, ComponentType aComponentType)
{
	std::vector<SComponentHandle>& componentList = myObjectToComponentListLUT[aGameObjectID];

	for (SComponentHandle& componentHandle : componentList)
	{
		if (componentHandle.myComponent->GetType() == aComponentType)
		{
			return componentHandle.myComponent;
		}
	}

	return nullptr;
}

//-----------------------------------------------------------
