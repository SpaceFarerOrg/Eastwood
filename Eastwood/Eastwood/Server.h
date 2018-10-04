#pragma once
#include "ConnectionBase.h"
#include <unordered_map>
#include "TimedEvent.h"

namespace Network
{
	class CServer : public CConnectionBase
	{
	public:
		CServer() = default;
		~CServer() = default;

		void Start(unsigned int aPort) override;
		void Update() override;
		void Stop() override;

		void SetName(const std::string& aName);

	private:

		struct SClient
		{
			std::string myName;
			unsigned short myID;
			float myTimeSinceLatestPing;
			bool myConnected;
		};

		void AddClient(sockaddr_in aAddress, const std::string& aName);
		void ReceivePing(unsigned long aID);
		void HandleClients();
		void DisconnectClient(SClient& aClientToDisconnect);

		unsigned long ConvertAddressToID(const sockaddr_in& aAddress);

		std::string myName;

		sockaddr_in myLocalAddress;

		std::unordered_map<unsigned long, SClient> myClients;
	};
}