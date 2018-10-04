#pragma once
#include "NetMessage.h"
#include "SmallString.h"

#include "SFML/System/Vector2.hpp"

namespace Network
{
	struct SNetMessagePlayerDataData : SNetMessageData
	{
		sf::Vector2f myPosition;
		float myRotation;
	};

	class CNetMessagePlayerData : public CNetMessage
	{
	public:
		void Create(SNetMessagePlayerDataData aData);
		SNetMessagePlayerDataData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessagePlayerDataData myData;
	};
}