#include "Renderer.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

CRenderer::CRenderer(const CMainSingleton& aMainSingleton)
{
}

void CRenderer::SetDimensions(unsigned int aW, unsigned int aH)
{
	myRenderTexture.create(aW, aH);
}

void CRenderer::PushRenderCommand(const sf::Sprite& aSprite)
{
	myRenderCommands.push_back(aSprite);
}

sf::Sprite CRenderer::RunRendering()
{
	for (sf::Sprite& sprite : myRenderCommands)
	{

		myRenderTexture.draw(sprite);
	}

	myRenderCommands.clear();

	myRenderTexture.display();

	sf::Sprite renderedImage;
	renderedImage.setTexture(myRenderTexture.getTexture());

	return std::move(renderedImage);
}

void CRenderer::Clear()
{
	myRenderTexture.clear();
}

