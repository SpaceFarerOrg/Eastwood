#pragma once

#include <vector>

class CCollider;

class CCollisionManager
{
public:
	void AddCollider(CCollider* aCollider);

	void Init();
	void Update();
	void Render();

private:

	std::vector<CCollider*> myColliders;
};