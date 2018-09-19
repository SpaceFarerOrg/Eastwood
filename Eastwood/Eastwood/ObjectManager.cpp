#include "ObjectManager.h"

#include "GameObject.h"

#include <assert.h>
#include <new.h>

#include "TransformComponent.h"

//-----------------------------------------------------------

CObjectManager::CObjectManager()
	: myComponentManager()
	, myNextObjectIndex(0)
	, myMaxObjectCount(0)
	, myObjectPool(nullptr)
{
}

//-----------------------------------------------------------

void CObjectManager::Initialize(unsigned int aMaxGameObjectCount)
{
	if (myObjectPool)
	{
		assert(false && "Object Pool already exist, possible duplicate call to CObjectManager::Initialize");
	}

	myMaxObjectCount = aMaxGameObjectCount;
	myObjectPool = new char[AsObjectIndex(myMaxObjectCount)]();
}

//-----------------------------------------------------------

void CObjectManager::BeginPlay()
{
	myComponentManager.OnStart();
}

//-----------------------------------------------------------

void CObjectManager::Tick(float aDT)
{
	for (unsigned int i = 0; i < myNextObjectIndex; ++i)
	{
		myComponentManager.TickComponentsForObject(i, aDT);
	}
}

//-----------------------------------------------------------

CComponentManager & CObjectManager::GetComponentManager()
{
	return myComponentManager;
}

//-----------------------------------------------------------

CGameObject & CObjectManager::GetGameObject(unsigned int aGameObjectID)
{
	return GetGameObjectAtIndex(aGameObjectID);
}

//-----------------------------------------------------------

CGameObject & CObjectManager::CreateGameObject()
{
	const unsigned int objectIndex = AsObjectIndex(myNextObjectIndex);
	
	if (objectIndex >= myMaxObjectCount)
	{
		assert(false && "Object Pool is full, initialize Object Manager with a higher object count!");
	}

	void* const addressOfNewObject = &myObjectPool[objectIndex];

	CGameObject* createdObject = new(addressOfNewObject) CGameObject(*this, myNextObjectIndex);

	++myNextObjectIndex;

	//Add transform components to all game objects
	createdObject->AddComponent(CTransformComponent());

	return *createdObject;
}

//-----------------------------------------------------------

void CObjectManager::DestroyObject(unsigned int aGameObjectID)
{
	myComponentManager.DestroyAllComponentsForObject(aGameObjectID);
}

//-----------------------------------------------------------

unsigned int CObjectManager::AsObjectIndex(unsigned int aRawIndex)
{
	return aRawIndex * sizeof(CGameObject);
}

//-----------------------------------------------------------

CGameObject & CObjectManager::GetGameObjectAtIndex(unsigned int aIndex)
{
	unsigned int gameObjectIndex = AsObjectIndex(aIndex);
	CGameObject* gameObjectPtr = reinterpret_cast<CGameObject*>(&myObjectPool[gameObjectIndex]);

	return *gameObjectPtr;
}

//-----------------------------------------------------------
