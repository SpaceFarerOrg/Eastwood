#pragma once
#include "ComponentManager.h"

class CGameObject;

class CObjectManager
{
public:
	CObjectManager();
	
	void Initialize(unsigned int aMaxGameObjectCount);
	void BeginPlay();
	void Tick(float aDT);

	CComponentManager& GetComponentManager();

	CGameObject& GetGameObject(unsigned int aGameObjectID);
	CGameObject& CreateGameObject();

private:
	CComponentManager myComponentManager;

	static unsigned int AsObjectIndex(unsigned int aRawIndex);
	CGameObject& GetGameObjectAtIndex(unsigned int aIndex);

	unsigned int myNextObjectIndex;
	unsigned int myMaxObjectCount;
	char* myObjectPool;
};