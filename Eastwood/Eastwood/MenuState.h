#pragma once
#include "State.h"

#include "UIManager.h"

class CMenuState : public CState
{
public:
	CMenuState();
	~CMenuState() override;

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;

private:
	CUIManager myUIManager;
};