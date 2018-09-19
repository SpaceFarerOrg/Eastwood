#pragma once
#include "ObjectManager.h"
#include "SFML/Graphics/Transformable.hpp"

#include "ComponentRuntimeDataDefines.h"

class CGameObject
{
public:
	CGameObject() = delete;
	CGameObject(CObjectManager& aObjectManager ,unsigned int aGameObjectID);
	
	void Destroy();

	unsigned int GetGameObjectID() const;
	void AddComponent(const CComponent& aNewComponent, void* aComponentCreationParams = nullptr) const;

	CComponent* GetComponent(ComponentType aComponentToGet);

private:
	CObjectManager& myObjectManager;
	unsigned int myGameObjectID;
};

