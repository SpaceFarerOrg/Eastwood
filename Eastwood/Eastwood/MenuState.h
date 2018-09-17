#pragma once
#include "State.h"

class CMenuState : public CState
{
public:
	CMenuState();
	~CMenuState();

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;
private:

};