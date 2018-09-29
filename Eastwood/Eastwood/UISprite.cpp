#include "UISprite.h"

CUISprite::~CUISprite()
{
}

void CUISprite::Init(JsonValue aElementJson)
{
	CUIElement::Init(aElementJson);

	myTexture.loadFromFile("Graphics/Textures/UI/" + std::string(aElementJson["texture"].GetString()));

	float width = (float)aElementJson["width"].GetInt();
	float height = (float)aElementJson["height"].GetInt();
	if (width != 0 && height != 0)
	{
		setScale(width / (float)myTexture.getSize().x, height / (float)myTexture.getSize().y);
	}

	setTexture(myTexture);
}

void CUISprite::Update()
{
	CUIElement::Update();
}

void CUISprite::Render(sf::RenderTarget * aTarget)
{
	//if (myName == "background")
	//{
	//	setScale()
	//}

	CUIElement::Render(aTarget); // Should be bottom
}
