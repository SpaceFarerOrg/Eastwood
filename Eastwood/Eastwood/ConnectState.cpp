#include "ConnectState.h"

#include "UITextInput.h"
#include "InputManager.h"
#include "GameState.h"

void CConnectState::Init()
{
	myUIManager.Init("UI/connect_menu.json");
}

void CConnectState::Update(float dt)
{
	myUIManager.Update(dt);

	CUITextInput* nameInput = myUIManager.GetElement<CUITextInput>("name_input");
	CUITextInput* ipInput = myUIManager.GetElement<CUITextInput>("ip_input");
	CUITextInput* portInput = myUIManager.GetElement<CUITextInput>("port_input");

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Enter) || myUIManager.CheckForEvent("connect"))
	{
		CGameState::SLaunchData launchData;
		launchData.myAddressToConnectTo = ipInput->GetText();
		launchData.myName = nameInput->GetText();
		launchData.myNetworkState = Network::ENetworkState::Client;
		launchData.myPort = std::stoi(portInput->GetText());

		Push(new CGameState(launchData));

		nameInput->Clear();
		ipInput->Clear();
		portInput->Clear();
	}
}

void CConnectState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
