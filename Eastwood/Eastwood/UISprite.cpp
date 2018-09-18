#include "UISprite.h"

void CUISprite::Init()
{
	myTexture.loadFromFile("Graphics/Textures/error.png");

	setTexture(myTexture);

	CUIElement::Init();
}

void CUISprite::Update()
{

	CUIElement::Update();
}

void CUISprite::Render(sf::RenderTarget * aTarget)
{
	aTarget->draw(*this);

	CUIElement::Render(aTarget); // Should be bottom
}
