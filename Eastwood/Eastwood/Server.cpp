#include "Server.h"
#include "Time.h"
#include "NetMessages.h"

void Network::CServer::Start(unsigned int aPort)
{
	CConnectionBase::Start(aPort);

	myPositionSender.Init(CTimedEvent::EType::Repeat, 1.f / 60.f, [this]() {
		SVector2Data data;
		for (const auto& pair : myClients)
		{
			const int clientID = pair.first;
			const SClient& client = pair.second;

			for (const auto& recPair : myClients)
			{
				//if (recPair.first == clientID)
					//continue;

				data.myTargetID = recPair.first;
				data.myType = ENetMessageType::PlayerPos;
				data.myVector2 = client.myData.myTransform.getPosition();
				data.myID = clientID;
				myMessageManager.CreateMessage<CNetMessageVector2>(data);
			}
		}
	});
	myPositionSender.Start();
}

void Network::CServer::Update()
{
	CConnectionBase::Update();
	float dt = CTime::GetInstance().GetDeltaTime();

	HandleClients();
	myPositionSender.Update(dt);

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		int clientID = rec.myFromAddress.toInteger();
		short type;
		rec.myPacket >> type;

		switch (static_cast<ENetMessageType>(type))
		{
		case ENetMessageType::Connect:
		{
			CNetMessageString msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			AddClient(clientID, rec.myFromPort, msg.GetString());
			break;
		}
		case ENetMessageType::Chat:
		{
			CNetMessageString msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			PRINT("Received: " << msg.GetString());
			break;
		}
		case ENetMessageType::PlayerPos:
		{
			CNetMessageVector2 msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			myClients[clientID].myData.myTransform.setPosition(msg.GetVector2());
			break;
		}
		}
	}
}

void Network::CServer::Stop()
{
	CConnectionBase::Stop();
}

void Network::CServer::SetName(const std::string & aName)
{
	myName = aName;
}

void Network::CServer::SendMessage(const std::string & aMessage)
{
	Network::SStringData msg;
	msg.myString = aMessage;
	msg.myTargetID = 0;
	msg.myType = Network::ENetMessageType::Chat;
	msg.myTimeStamp = 1337;
	msg.myID = 777;

	myMessageManager.CreateMessage<CNetMessageString>(msg);
}

void Network::CServer::AddClient(int aAddress, int aPort, const std::string& aName)
{
	SClient nClient;
	nClient.myConnected = true;
	nClient.myID = aAddress;
	nClient.myName = aName;
	nClient.myTimeSinceLatestPing = 0.f;

	myClients.insert(std::make_pair(aAddress, nClient));
	myMessageManager.AddReceiver(sf::IpAddress(aAddress), aPort);

	PRINT("Client " << aName << " connected!");

	SBaseData response;
	response.myTargetID = nClient.myID;
	response.myType = ENetMessageType::Connect;
	myMessageManager.CreateMessage<CNetMessage>(response);

	// Send to other clients
	for (const auto& pair : myClients)
	{
		if (pair.first == aAddress)
			continue;

		// New client to other
		SBaseData data;
		data.myID = aAddress;
		data.myTargetID = pair.first;
		data.myType = ENetMessageType::NewPlayer;
		myMessageManager.CreateMessage<CNetMessage>(data);

		// Other client to new
		SBaseData otherData;
		otherData.myID = pair.first;
		otherData.myTargetID = aAddress;
		otherData.myType = ENetMessageType::NewPlayer;
		myMessageManager.CreateMessage<CNetMessage>(otherData);
	}
}

void Network::CServer::HandleClients()
{
}

void Network::CServer::DisconnectClient(SClient & aClient)
{
}