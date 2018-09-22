#include "UISprite.h"

CUISprite::~CUISprite()
{
}

void CUISprite::Init(JsonValue aElementJson)
{
	CUIElement::Init(aElementJson);

	myTexture.loadFromFile(aElementJson["texture"].GetString());

	if (aElementJson["width"].GetInt() == 0 || aElementJson["height"].GetInt() == 0)
	{
		myRenderTexture.create(myTexture.getSize().x, myTexture.getSize().y);
	}
	float sx = (float)myRenderTexture.getSize().x / myTexture.getSize().x;
	float sy = (float)myRenderTexture.getSize().y / myTexture.getSize().y;
	setScale(sx, sy);

	setTexture(myTexture);
	SetEventName("Sprite");
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
