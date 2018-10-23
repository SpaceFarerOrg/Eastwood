#pragma once
#include <memory>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class CWorldZone
{
public:
	void Create();
	void Render(const sf::FloatRect& aRenderRectangle = { 16,0,500,900 });
private:
	void CreateMockMap();
	bool ShouldCullTile(float aX, float aY, const sf::FloatRect& aRenderRectangle);
	std::unique_ptr<short[]> myMap;
	sf::Texture myTilesheet;
	sf::Sprite myAirTile;
	sf::Sprite myRockTile;
	int myWidth;
	int myHeight;
};