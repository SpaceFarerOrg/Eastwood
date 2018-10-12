#pragma once
#include "UIElement.h"
#include "Graphics/Text.hpp"
#include "Graphics/RectangleShape.hpp"

#include <unordered_set>

class CUITextInput : public CUIElement
{
public:

	~CUITextInput() override;

	virtual void Init(JsonValue aElementJson) override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* aTarget) override;

	std::string GetText();
	void Clear();

private:
	void InputString(const std::string& aString);

	float myCaretTimer;
	bool myCaretIsVisible;
	sf::Font myFont;
	sf::Text myText;
	sf::RectangleShape myCaret;
	sf::RectangleShape myBox;
	std::unordered_set<char> myAllowedCharacters;
};