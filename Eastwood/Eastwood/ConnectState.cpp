#include "ConnectState.h"

void CConnectState::Init()
{
	myUIManager.Init("UI/connect_menu.json");
}

void CConnectState::Update(float dt)
{
	myUIManager.Update(dt);
}

void CConnectState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
