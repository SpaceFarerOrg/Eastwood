#include "Server.h"
#include <string>
#include "Time.h"

void Network::CServer::Start(unsigned int aPort)
{

	PRINT("Starting up server...");
	CConnectionBase::Start(aPort);

	unsigned short port = aPort;
	myLocalAddress.sin_family = AF_INET;
	myLocalAddress.sin_port = htons(port);
	myLocalAddress.sin_addr.s_addr = INADDR_ANY;

	int error = bind(mySocket, (sockaddr*)&myLocalAddress, sizeof(myLocalAddress));
	if (error != 0)
	{
		PRINT("Binding of local address failed with error code: " + std::to_string(error));
		return;
	}

	PRINT("Listening for new connections on port: " + std::to_string(port));
}

void Network::CServer::Update()
{
	CConnectionBase::Update();

	float dt = CTime::GetInstance().GetDeltaTime();

	HandleClients();

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		unsigned long senderID = ConvertAddressToID(rec.myFromAddress);
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
			ReceivePing(senderID);
			break;
		}
		case Network::ENetMessageType::Connect:
		{
			CNetMessageConnect msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageConnectData));
			msg.Unpack();
			AddClient(rec.myFromAddress, msg.GetData().myName.ToString());
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

void Network::CServer::AddClient(sockaddr_in aAddress, const std::string & aName)
{
	unsigned long ID = aAddress.sin_addr.S_un.S_addr;

	if (myClients.find(ID) == myClients.end())
	{
		SClient newClient;
		newClient.myName = aName;
		newClient.myID = myClients.size();
		newClient.myTimeSinceLatestPing = 0;
		newClient.myConnected = true;

		myClients.insert(std::make_pair(ID, newClient));
		PRINT(aName + " connected!");

		SNetMessageConnectData response;
		response.myName = "Server";
		response.myTargetID = newClient.myID;
		
		myMessageManager.CreateMessage<CNetMessageConnect>(response);
		myMessageManager.AddReceiver(aAddress);

		for (auto& client : myClients)
		{
			if (client.first == ID)
				continue;

			// New to existing
			SNetMessageData newPlayerMessage;
			newPlayerMessage.myTargetID = client.second.myID;
			newPlayerMessage.myType = ENetMessageType::NewPlayer;
			newPlayerMessage.myID = newClient.myID;

			myMessageManager.CreateMessage<CNetMessage>(newPlayerMessage);

			// Existing to new
			newPlayerMessage.myTargetID = newClient.myID;
			newPlayerMessage.myType = ENetMessageType::NewPlayer;
			newPlayerMessage.myID = client.second.myID;

			myMessageManager.CreateMessage<CNetMessage>(newPlayerMessage);
		}
	}
	else if (myClients[ID].myConnected == false)
	{
		myClients[ID].myConnected = true;
		myClients[ID].myTimeSinceLatestPing = 0;
		PRINT(aName + " reconnected!");
	}
	else
	{
		PRINT("Tried to add an already existing client.");
	}
}

void Network::CServer::ReceivePing(unsigned long aID)
{
	SClient& client = myClients[aID];
	client.myTimeSinceLatestPing = 0.f;
	if (client.myConnected == false)
	{
		client.myConnected = true;
		PRINT(client.myName + " reconnected!");
	}
	else
	{
		PRINT("Received ping from " + std::to_string(myClients[aID].myID));
	}
}

void Network::CServer::HandleClients()
{
	float dt = CTime::GetInstance().GetDeltaTime();

	for (auto& clientPair : myClients)
	{
		if (clientPair.second.myConnected == false)
			continue;

		clientPair.second.myTimeSinceLatestPing += dt;

		if (clientPair.second.myTimeSinceLatestPing > PING_TIMEOUT)
		{
			DisconnectClient(clientPair.second);
		}
	}
}

void Network::CServer::DisconnectClient(SClient & aClientToDisconnect)
{
	aClientToDisconnect.myConnected = false;

	PRINT("Client " + std::to_string(aClientToDisconnect.myID) + " disconnected.");
}

unsigned long Network::CServer::ConvertAddressToID(const sockaddr_in & aAddress)
{
	return aAddress.sin_addr.S_un.S_addr;
}
