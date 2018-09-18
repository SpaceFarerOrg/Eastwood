#include "Renderer.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

CRenderer::CRenderer()
	: myIsCreated(false)
{
}

void CRenderer::Create(unsigned int aW, unsigned int aH)
{
	myIsCreated = true;
	myRenderTexture.create(aW, aH);
}

void CRenderer::PushRenderCommand(sf::Drawable & aRenderable)
{
	myRenderCommands.push_back(&aRenderable);
}

sf::Sprite CRenderer::RunRendering()
{
	for (sf::Drawable* drawable : myRenderCommands)
	{
		myRenderTexture.draw(*drawable);
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

bool CRenderer::IsCreated() const
{
	return myIsCreated;
}
