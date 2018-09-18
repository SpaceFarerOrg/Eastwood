#include "UISprite.h"

void CUISprite::Init()
{
	myTexture.loadFromFile("Graphics/Textures/error.png");

	setTexture(myTexture);
	SetEventName("Sprite");
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
