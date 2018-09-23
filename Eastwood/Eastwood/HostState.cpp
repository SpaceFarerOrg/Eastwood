#include "HostState.h"

void CHostState::Init()
{
	myUIManager.Init("UI/host_menu.json");
}

void CHostState::Update(float dt)
{
	myUIManager.Update(dt);
}

void CHostState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
