#include "MenuState.h"
#include <iostream>
#include "InputManager.h"
#include "GameState.h"
#include "SettingsState.h"
#include "HostState.h"
#include "ConnectState.h"

CMenuState::CMenuState()
{
}

CMenuState::~CMenuState()
{
	myUIManager.Destroy();
}

void CMenuState::Init()
{
	std::cout << "Pushed MenuState" << std::endl;

	myUIManager.Init("UI/main_menu.json");
}

void CMenuState::Update(float dt)
{
	myUIManager.Update(dt);

	if (myUIManager.CheckForEvent("singleplayer"))
	{
		Push(new CGameState());
	}
	else if (myUIManager.CheckForEvent("settings"))
	{
		Push(new CSettingsState());
	}
	else if (myUIManager.CheckForEvent("host"))
	{
		Push(new CHostState());
	}
	else if (myUIManager.CheckForEvent("connect"))
	{
		Push(new CConnectState());
	}
	else if (myUIManager.CheckForEvent("quit"))
	{
		PopAll();
	}
}

void CMenuState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
