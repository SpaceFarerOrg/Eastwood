#pragma once
#include "CommonNetworkIncludes.h"

namespace Network
{
	class CConnectionBase
	{

	public:

		virtual void Start(unsigned int aPort);
		virtual void Update();
		virtual void Stop();

	protected:

		struct SReceivedMessage
		{
			char myBuffer[MAX_BUFFER_SIZE];
			sockaddr_in myFromAddress;
		};

		SOCKET mySocket;

		unsigned int mySentThisSecond;
		float mySentTimer;

		CNetMessageManager myMessageManager;
		std::vector<SReceivedMessage> myReceivedBuffer;
	};
}