#pragma once
#include "State.h"

#include "UIManager.h"

class CConnectState : public CState
{
public:
	CConnectState() = default;
	~CConnectState() override { myUIManager.Destroy(); };

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;

private:
	CUIManager myUIManager;
};