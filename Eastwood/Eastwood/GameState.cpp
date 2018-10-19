#include "GameState.h"
#include "InputManager.h"
#include <iostream>
#include "MenuState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Renderer.h"
#include "MainSingelton.h"
#include "NetMessages.h"

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

	CMainSingleton::GetRenderer().SetDimensions(1600, 900);

	myPlayer.Init();
}

void CGameState::Update(float dt)
{
	myPlayer.Update(dt);

	if (myLaunchData.myNetworkState != Network::ENetworkState::Singleplayer)
	{
		HandleNetworking(dt);
	}
}

void CGameState::Render(sf::RenderWindow * aRenderWindow)
{
	CRenderer& renderer = CMainSingleton::GetRenderer();

	myPlayer.Render();

	for (auto& other : myOtherPlayers)
	{
		other.second.Render();
	}

	sf::Sprite renderedImage = renderer.RunRendering();
	aRenderWindow->draw(renderedImage);

	renderer.Clear();
}

void CGameState::AddPlayer(int aID)
{
	myOtherPlayers[aID] = CPlayer();
	myOtherPlayers[aID].Init();
}

void CGameState::UpdateOtherPlayer(int aID, const sf::Vector2f & aPosition)
{
	CPlayer& player = myOtherPlayers[aID];
	player.GetTransform().setPosition(aPosition);
	player.Update(0);
	
}

void CGameState::SetupNetworking()
{
	if (myLaunchData.myNetworkState == Network::ENetworkState::Singleplayer)
		return;

	myClient.BindGame(this);
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

	myPositionSender.Init(CTimedEvent::EType::Repeat, 1.f / 60.f, [this]() {
		Network::SVector2Data data;
		data.myVector2 = myPlayer.GetTransform().getPosition();
		data.myTargetID = 0;
		data.myType = Network::ENetMessageType::PlayerPos;
		data.myID = myClient.GetID();
		myClient.GetMessageManager().CreateMessage<Network::CNetMessageVector2>(data);
	});
	myPositionSender.Start();

	//CComponent::BindNetMessageManager(myClient.GetMessageManager());
}

void CGameState::HandleNetworking(float dt)
{
	myPositionSender.Update(dt);

	myClient.Update();

	if (myLaunchData.myNetworkState == Network::ENetworkState::Server)
	{
		myServer.Update();
	}
}
