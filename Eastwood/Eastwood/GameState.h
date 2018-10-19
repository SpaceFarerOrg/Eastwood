#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "SFML/Graphics/Texture.hpp"
#include "Player.h"
#include "TimedEvent.h"

#include "CommonNetworkIncludes.h"
#include "Server.h"
#include "Client.h"

class CGameState : public CState
{
public:

	struct SLaunchData
	{
		Network::ENetworkState myNetworkState;
		std::string myAddressToConnectTo;
		std::string myName;
		unsigned int myPort;
	};

	CGameState();
	CGameState(const SLaunchData& aLaunchData);
	~CGameState();

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;

	void AddPlayer(int aID);
	void UpdateOtherPlayer(int aID, const sf::Vector2f& aPosition);

private:
	void SetupNetworking();
	void HandleNetworking(float dt);

	SLaunchData myLaunchData;

	sf::Texture myTestTexture;
	CObjectManager myObjectManager;

	CPlayer myPlayer;
	std::unordered_map<int, CPlayer> myOtherPlayers;

	// Network stuff

	Network::CClient myClient;
	Network::CServer myServer;

	CTimedEvent myPositionSender;
};

