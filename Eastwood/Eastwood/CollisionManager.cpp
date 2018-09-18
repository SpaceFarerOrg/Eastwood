#include "CollisionManager.h"
#include "Collider.h"

void CCollisionManager::AddCollider(CCollider * aCollider)
{
	myColliders.push_back(aCollider);
}

void CCollisionManager::Init()
{
}

void CCollisionManager::Update()
{
}
