#pragma once
#include "NetMessage.h"
#include "SFML/System/Vector2.hpp"

namespace Network
{
	struct SNetMessagePositionData : SNetMessageData
	{
		sf::Vector2f myPosition;
	};

	class CNetMessagePosition: public CNetMessage
	{
	public:
		void Create(SNetMessagePositionData aData);
		SNetMessagePositionData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessagePositionData myData;
	};
}