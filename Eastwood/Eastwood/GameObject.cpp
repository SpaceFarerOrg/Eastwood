#include "GameObject.h"

//-----------------------------------------------------------

CGameObject::CGameObject(CObjectManager& aObjectManager, unsigned int aGameObjectID)
	: myObjectManager(aObjectManager)
	, myGameObjectID(aGameObjectID)
{
}

void CGameObject::Destroy()
{
	myObjectManager.DestroyObject(myGameObjectID);
}

//-----------------------------------------------------------

unsigned int CGameObject::GetGameObjectID() const
{
	return myGameObjectID;
}

//-----------------------------------------------------------

void CGameObject::AddComponent(const CComponent & aNewComponent, void* aComponentCreationParams) const
{
	CComponent& createdComponent = myObjectManager.GetComponentManager().CreateComponent(aNewComponent, myGameObjectID, aComponentCreationParams);
	createdComponent.BindOwner(myObjectManager.GetGameObject(myGameObjectID));
}

CComponent * CGameObject::GetComponent(ComponentType aComponentToGet)
{
	return myObjectManager.GetComponentManager().GetComponent(myGameObjectID, aComponentToGet);
}

//-----------------------------------------------------------