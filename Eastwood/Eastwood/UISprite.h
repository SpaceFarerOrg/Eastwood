#pragma once
#include "UIElement.h"

class CUISprite : public CUIElement
{
public:

	~CUISprite() override;

	virtual void Init(JsonValue aElementJson) override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* aTarget) override;

private:
	sf::Texture myTexture;
};