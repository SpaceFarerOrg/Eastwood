#pragma once
#include "State.h"
#include "ObjectManager.h"

class CGameState : public CState
{
public:
	CGameState();
	~CGameState();

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;
private:
	CObjectManager myObjectManager;
};

