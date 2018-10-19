#pragma once
#include "ConnectionBase.h"

class CGameState;

namespace Network
{
	class CClient : public CConnectionBase
	{
	public:
		CClient() = default;
		~CClient() = default;

		void Start(unsigned int aPort) override;
		void Update() override;
		void Stop() override;

		void TryToConnect(const std::string& aMyName, sf::IpAddress aAddress, unsigned int aPort);

		void BindGame(CGameState* aGame);
		int GetID();

	private:

		sf::IpAddress myLocalAddress;
		sf::IpAddress myPublicAddress;
		sf::IpAddress myServerAddress;
		unsigned int myServerPort;

		CGameState* myGame;
	};
}