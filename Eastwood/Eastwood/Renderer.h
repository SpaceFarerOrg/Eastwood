#pragma once
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

namespace sf
{
	class Renderable;
	class RenderTexture;
}

class CRenderer
{
public:
	CRenderer();

	void Create(unsigned int aW, unsigned int aH);

	void PushRenderCommand(sf::Drawable& aRenderable);
	sf::Sprite RunRendering();
	void Clear();

	bool IsCreated() const;
private:
	bool myIsCreated;
	sf::RenderTexture myRenderTexture;
	std::vector<sf::Drawable*> myRenderCommands;
};