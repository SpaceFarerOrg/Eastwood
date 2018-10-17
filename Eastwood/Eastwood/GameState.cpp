#include "GameState.h"
#include "InputManager.h"
#include <iostream>
#include "MenuState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Renderer.h"
#include "MainSingelton.h"

CGameState::CGameState()
{
}

CGameState::CGameState(const SLaunchData& aLaunchData)
{
	myLaunchData = aLaunchData;

	std::cout << "Started Game as " << (myLaunchData.myNetworkState == Network::ENetworkState::Singleplayer ? "Singleplayer" : (myLaunchData.myNetworkState == Network::ENetworkState::Server ? "Server" : "Client")) << std::endl;
}


CGameState::~CGameState()
{
}

void CGameState::Init()
{
	std::cout << "Pushed GameState" << std::endl;

	SetupNetworking();

	myTestTexture.loadFromFile("playerShip.png");

	CMainSingleton::GetRenderer().SetDimensions(1600, 800);

	myPlayer.Init();
}

void CGameState::Update(float dt)
{
	myPlayer.Update(dt);

	myServer.Update();
	myClient.Update();
}

void CGameState::Render(sf::RenderWindow * aRenderWindow)
{
	CRenderer& renderer = CMainSingleton::GetRenderer();

	myPlayer.Render();

	sf::Sprite renderedImage = renderer.RunRendering();
	aRenderWindow->draw(renderedImage);

	renderer.Clear();
}

void CGameState::SetupNetworking()
{
	if (myLaunchData.myNetworkState == Network::ENetworkState::Singleplayer)
		return;

	if (myLaunchData.myNetworkState == Network::ENetworkState::Server)
	{
		myServer.SetName(myLaunchData.myName);
		myServer.Start(myLaunchData.myPort);
		myClient.Start(0);
		myClient.TryToConnect(myLaunchData.myName, myLaunchData.myAddressToConnectTo, myLaunchData.myPort);
	}
	if (myLaunchData.myNetworkState == Network::ENetworkState::Client)
	{
		myClient.Start(0);
		myClient.TryToConnect(myLaunchData.myName, myLaunchData.myAddressToConnectTo, myLaunchData.myPort);
	}

	//CComponent::BindNetMessageManager(myClient.GetMessageManager());
}
