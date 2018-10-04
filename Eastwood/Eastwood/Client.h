#pragma once
#include "ConnectionBase.h"
#include "TimedEvent.h"

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

		void TryToConnect(const std::string& aName, const std::string& aIP, unsigned int aPort);

	private:

		void PingServer();

		sockaddr_in myLocalAddress;
		sockaddr_in myServerAddress;

		unsigned int myServerPort;

		CTimedEvent myPingTimer;
	};
}