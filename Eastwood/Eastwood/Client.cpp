#include "Client.h" 
#include "NetMessages.h" 
#include "GameState.h"

void Network::CClient::Start(unsigned int aPort)
{
	CConnectionBase::Start(aPort);
	myPublicAddress = sf::IpAddress::getPublicAddress();
	myLocalAddress = sf::IpAddress::getLocalAddress();
}

void Network::CClient::Update()
{
	CConnectionBase::Update();

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		short type;
		rec.myPacket >> type;

		switch (static_cast<ENetMessageType>(type))
		{
		case ENetMessageType::Chat:
		{
			CNetMessageString msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			PRINT("Received: " + msg.GetString());
			break;
		}
		case ENetMessageType::Connect:
		{
			CNetMessage msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			PRINT("Connected to server. Congratulations!");
			break;
		}
		case ENetMessageType::PlayerPos:
		{
			CNetMessageVector2 msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			myGame->UpdateOtherPlayer(msg.GetBaseData().myID, msg.GetVector2());
			break;
		}
		case ENetMessageType::NewPlayer:
		{
			CNetMessage msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			PRINT("Player joined!");
			myGame->AddPlayer(msg.GetBaseData().myID);
			break;
		}
		}
	}
}

void Network::CClient::Stop()
{
	CConnectionBase::Stop();
}

void Network::CClient::TryToConnect(const std::string& aMyName, sf::IpAddress aAddress, unsigned int aPort)
{
	myServerAddress = aAddress;
	myServerPort = aPort;

	myMessageManager.AddReceiver(aAddress, aPort);

	SStringData connectMsg;
	connectMsg.myTargetID = aAddress.toInteger();
	connectMsg.myType = ENetMessageType::Connect;
	connectMsg.myString = aMyName;

	myMessageManager.CreateMessage<CNetMessageString>(connectMsg);
}

void Network::CClient::BindGame(CGameState * aGame)
{
	myGame = aGame;
}

int Network::CClient::GetID()
{
	return myPublicAddress.toInteger();
}
