#include "Client.h"
#include "NetMessageChat.h"
#include "Time.h"
#include "NetMessageConnect.h"

void Network::CClient::Start(unsigned int aPort)
{
	PRINT("Starting up client...");
	CConnectionBase::Start(aPort);

	myLocalAddress.sin_family = AF_INET;
	myLocalAddress.sin_port = 0;
	myLocalAddress.sin_addr.s_addr = INADDR_ANY;

	int error = bind(mySocket, (sockaddr*)&myLocalAddress, sizeof(myLocalAddress));
	if (error != 0)
	{
		PRINT("Binding of local address failed with error code: " + std::to_string(error));
		return;
	}

	myPingTimer.Init(CTimedEvent::EType::Repeat, FREQ_PING, [this]() { PingServer(); });
}

void Network::CClient::Update()
{
	CConnectionBase::Update();

	float dt = CTime::GetInstance().GetDeltaTime();

	myPingTimer.Update(dt);

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		char* buffer = rec.myBuffer;
		ENetMessageType type = static_cast<ENetMessageType>(buffer[0]);

		switch (type)
		{
		case Network::ENetMessageType::Chat:
		{
			CNetMessageChat msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageChatData));
			msg.Unpack();
			PRINT("Received: " + msg.GetData().myMessage.ToString());
			break;
		}
		case Network::ENetMessageType::Ping:
		{
			PRINT("Received ping from server");
			break;
		}
		case Network::ENetMessageType::Connect:
		{
			CNetMessageConnect msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageConnectData));
			msg.Unpack();
			PRINT("Connected to " + msg.GetData().myName.ToString());
			myPingTimer.Start();
			break;
		}
		case ENetMessageType::NewPlayer:
		{
			CNetMessage msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageData));
			msg.Unpack();

			break;
		}
		case ENetMessageType::PlayerData:
		{
			CNetMessagePlayerData msg;
			msg.ReceiveData(buffer, sizeof(SNetMessagePlayerDataData));
			msg.Unpack();

			break;
		}
		}
	}
}

void Network::CClient::Stop()
{
	CConnectionBase::Stop();
}

void Network::CClient::TryToConnect(const std::string & aName, const std::string & aIP, unsigned int aPort)
{
	myServerPort = aPort;
	inet_pton(AF_INET, aIP.c_str(), &myServerAddress.sin_addr.s_addr);
	myServerAddress.sin_port = htons(aPort);
	myServerAddress.sin_family = AF_INET;
	myMessageManager.AddReceiver(myServerAddress);

	SNetMessageConnectData ping;
	ping.myTargetID = 0;
	ping.myType = ENetMessageType::Connect;
	ping.myName = aName.c_str();

	myMessageManager.CreateMessage<CNetMessageConnect>(ping);
}

void Network::CClient::PingServer()
{
	SNetMessageData ping;
	ping.myTargetID = 0;
	ping.myType = ENetMessageType::Ping;

	myMessageManager.CreateMessage<CNetMessage>(ping);
}
