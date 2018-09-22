#pragma once
#include <typeinfo>
#include <utility>

#include "ComponentRuntimeDataDefines.h"

class CGameObject;

struct SRawComponentData
{
	void* myAddress;
	size_t mySizeof;
};

class CComponent
{
public:
	CComponent();
	CComponent(CComponent* aAddress, size_t aSizeofComponent);

	virtual void OnCreated(void* aCreationParams = nullptr);
	virtual void OnStart();
	virtual void Tick(float aDT);
	virtual void OnDestroy() = 0;

	bool ShouldTick() const;


	const SRawComponentData& GetRawData() const;
	void BindOwner(CGameObject& aGameObject);

	virtual ComponentType GetType() const = 0;

protected:
	CGameObject& GetOwner();

	void SetShouldTick(bool aShouldTick);

	template<typename T>
	T CastToCustomInParams(void* aCreationParams) const;

private:
	SRawComponentData myRawData;
	CGameObject* myOwnerObject;
	bool myShouldTick : 1;
};

template<typename T>
inline T CComponent::CastToCustomInParams(void * aCreationParams) const
{
	T* castedParams = static_cast<T*>(aCreationParams);

	return std::move(*castedParams);
}
