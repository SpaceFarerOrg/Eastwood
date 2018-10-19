#pragma once

#include <iostream>
#include <string>

#include "SFML/Network.hpp"

#include "NetMessageManager.h"

#define MAX_BUFFER_SIZE 512

#define PRINT(a) std::cout << a << std::endl

namespace Network
{
	enum class ENetMessageType : short
	{
		Chat,
		Ping,
		Connect,
		PlayerPos,
		NewPlayer
	};

	enum class ENetworkState
	{
		Singleplayer,
		Client,
		Server
	};
}