#include "WorldZone.h"
#include "MainSingelton.h"
#include "Renderer.h"

void CWorldZone::Create()
{
	//Currently hard coded because of me not wanting to load crap :D 
	myWidth = 100;
	myHeight = 1000;

	myTilesheet.loadFromFile("Graphics/Textures/tempTileSheet.png");
	myAirTile.setTexture(myTilesheet);
	myAirTile.setTextureRect({ 0,0,64,64 });
	myRockTile.setTexture(myTilesheet);
	myRockTile.setTextureRect({ 64,0,64,64 });

	myMap = std::make_unique<short[]>(myWidth * myHeight);

	CreateMockMap();
}

void CWorldZone::Render(const sf::FloatRect& aRenderRectangle)
{
	const int mapArraySize = myWidth * myHeight;
	const float tileSize = 64.f;

	for (int i = 0; i < mapArraySize; ++i)
	{
		int x = i % myWidth;
		int y = i / myWidth;
		float fx = static_cast<float>(x);
		float fy = static_cast<float>(y);
		fx *= 64.f; //These should be tilesize
		fy *= 64.f; //These should be tilesize

		if (ShouldCullTile(fx, fy, aRenderRectangle))
		{
			continue;
		}

		sf::Sprite& relevantSprite = myMap[i] == 0 ? myAirTile : myRockTile;
		relevantSprite.setPosition(fx, fy);

		CMainSingleton::GetRenderer().PushRenderCommand(relevantSprite, 0);
	}
}

void CWorldZone::CreateMockMap()
{
	const int mapArraySize = myWidth * myHeight;

	for (int i = 0; i < mapArraySize; ++i)
	{
		int y = i / myWidth;

		myMap[i] = 0;

		if (y > 2)
		{
			myMap[i] = 1;
		}
	}
}

bool CWorldZone::ShouldCullTile(float aX, float aY, const sf::FloatRect & aRenderRectangle)
{
	bool shouldCull = true;

	if (aRenderRectangle.contains(aX, aY))
	{
		shouldCull = false;
	}

	return shouldCull;
}
