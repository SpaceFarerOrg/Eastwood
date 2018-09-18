#include "Component.h"
#include <assert.h>

//-----------------------------------------------------------

CComponent::CComponent()
	: myShouldTick(true)
	, myOwnerObject(nullptr)
{
}

//-----------------------------------------------------------

CComponent::CComponent(CComponent* aAddress, size_t aSizeofComponent)
	: myShouldTick(true)
	, myOwnerObject(nullptr)
{
	myRawData.myAddress = static_cast<void*>(aAddress);
	myRawData.mySizeof = aSizeofComponent;
}

//-----------------------------------------------------------

void CComponent::OnCreated(void * aCreationParams)
{
}

//-----------------------------------------------------------

void CComponent::OnStart()
{
}

//-----------------------------------------------------------

void CComponent::Tick(float aDT)
{
}

//-----------------------------------------------------------

bool CComponent::ShouldTick() const
{
	return myShouldTick;
}

//-----------------------------------------------------------

const SRawComponentData & CComponent::GetRawData() const
{
	return myRawData;
}

//-----------------------------------------------------------

void CComponent::BindOwner(CGameObject& aGameObject)
{
	if (myOwnerObject)
	{
		assert(false && "Tried to bind owner to component that already has owner");
	}

	myOwnerObject = &aGameObject;
}

//-----------------------------------------------------------

CGameObject & CComponent::GetOwner()
{
	return *myOwnerObject;
}

//-----------------------------------------------------------

void CComponent::SetShouldTick(bool aShouldTick)
{
	myShouldTick = aShouldTick;
}

//-----------------------------------------------------------
