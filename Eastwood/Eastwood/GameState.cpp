#include "GameState.h"
#include "InputManager.h"
#include <iostream>
#include "MenuState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "RenderableComponent.h"

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

	myObjectManager.Initialize(512);

	SRenderableComponentParam renderableCompData;
	renderableCompData.myRenderer = &myRenderer;
	renderableCompData.myTexture = &myTestTexture;

	myObjectManager.BeginPlay();
}

void CGameState::Update(float dt)
{
	myServer.Update();
	myClient.Update();

	myObjectManager.Tick(dt);
}

void CGameState::Render(sf::RenderWindow * aRenderWindow)
{
	if (!myRenderer.IsCreated())
	{
		myRenderer.Create(aRenderWindow->getSize().x, aRenderWindow->getSize().y);
	}

	sf::Sprite renderedImage = myRenderer.RunRendering();
	aRenderWindow->draw(renderedImage);

	myRenderer.Clear();
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
