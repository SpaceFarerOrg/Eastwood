#pragma once
#pragma once
#include "State.h"

#include "UIManager.h"

class CHostState : public CState
{
public:
	CHostState() = default;
	~CHostState() override { myUIManager.Destroy(); };

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;

private:
	CUIManager myUIManager;
};