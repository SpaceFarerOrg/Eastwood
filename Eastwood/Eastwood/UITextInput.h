#pragma once
#include "UIElement.h"
#include "Graphics/Text.hpp"
#include "Graphics/RectangleShape.hpp"

class CUITextInput : public CUIElement
{
public:

	~CUITextInput() override;

	virtual void Init(JsonValue aElementJson) override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* aTarget) override;

	std::string GetText();

private:
	float myCaretTimer;
	bool myCaretIsVisible;
	sf::Font myFont;
	sf::Text myText;
	sf::RectangleShape myCaret;
	sf::RectangleShape myBox;
};