#pragma once
#include "UIElement.h"

class CUISprite : public CUIElement
{
public:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* aTarget) override;

private:
	sf::Texture myTexture;
};