#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "SFML/Graphics/Texture.hpp"
#include "CommonNetworkIncludes.h"

#include "Server.h"
#include "Client.h"

class CGameState : public CState
{
public:

	struct SLaunchData
	{
		Network::ENetworkState myNetworkState;
		sf::IpAddress myAddressToConnectTo;
		std::string myName;
		unsigned int myPort;
	};

	CGameState();
	CGameState(const SLaunchData& aLaunchData);
	~CGameState();

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;
private:
	void SetupNetworking();

	SLaunchData myLaunchData;

	sf::Texture myTestTexture;
	CObjectManager myObjectManager;
	CRenderer myRenderer;

	Network::CClient myClient;
	Network::CServer myServer;
};

