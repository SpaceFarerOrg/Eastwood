#pragma once
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

namespace sf
{
	class Renderable;
	class RenderTexture;
}

class CMainSingleton;

class CRenderer
{
public:
	CRenderer() = delete;
	CRenderer(const CMainSingleton& aMainSingleton); //Takes a main singleton to ensure no construction is done outside of it

	void SetDimensions(unsigned int aW, unsigned int aH);

	void PushRenderCommand(sf::Drawable& aRenderable);
	sf::Sprite RunRendering();
	void Clear();

private:
	sf::RenderTexture myRenderTexture;
	std::vector<sf::Drawable*> myRenderCommands;
};