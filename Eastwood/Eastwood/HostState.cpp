#include "HostState.h"

#include <iostream>

#include "InputManager.h"
#include "UITextInput.h"
#include "GameState.h"

void CHostState::Init()
{
	myUIManager.Init("UI/host_menu.json");
}

void CHostState::Update(float dt)
{
	myUIManager.Update(dt);
	CUITextInput* portInput = myUIManager.GetElement<CUITextInput>("port_input");
	CUITextInput* serverNameInput = myUIManager.GetElement<CUITextInput>("server_name_input");
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Enter) || myUIManager.CheckForEvent("connect"))
	{
		CGameState::SLaunchData launchData;
		//launchData.myAddressToConnectTo = "127.0.0.1";
		launchData.myAddressToConnectTo = "85.235.23.240";
		launchData.myName = serverNameInput->GetText();
		launchData.myNetworkState = Network::ENetworkState::Server;
		launchData.myPort = std::stoi(portInput->GetText());

		Push(new CGameState(launchData));

		portInput->Clear();
		serverNameInput->Clear();
	}
}

void CHostState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}

void CHostState::GoToGame(const std::string & aServerName, unsigned int aPort)
{
}
