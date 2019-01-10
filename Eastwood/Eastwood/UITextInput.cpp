#include "UITextInput.h"
#include "InputManager.h"
#include "Time.h"
#include "SFML/Window/Clipboard.hpp"

CUITextInput::~CUITextInput()
{
}

void CUITextInput::Init(JsonValue aElementJson)
{
	CUIElement::Init(aElementJson);

	myFont.loadFromFile("Graphics/Fonts/default.ttf");
	myText.setFont(myFont);
	myText.setOrigin(-10, myText.getCharacterSize() / 2.f);
	myText.setString(aElementJson["defaultText"].GetString());

	myBox.setFillColor(sf::Color::Black);
	myBox.setSize(myCollider.GetSize());
	myBox.setPosition(getPosition());

	myCaretTimer = 0.f;
	myCaretIsVisible = true;
	myCaret.setFillColor(sf::Color::White);
	myCaret.setSize({2.f, (float)myText.getCharacterSize() + 2.f});
	myCaret.setOrigin(0.f, myCaret.getSize().y / 2);
	myCaret.setPosition(myText.getPosition().x + myText.getGlobalBounds().width, myText.getPosition().y);

	std::string type = aElementJson["type"].GetString();

	if (type == "textinput")
	{
		for (char c = 32; c < 126; ++c)
		{
			myAllowedCharacters.insert(c);
		}
	}
	else
	{
		char characters[10] = { '0','1','2','3','4','5','6','7','8','9' };
		for (char c : characters)
			myAllowedCharacters.insert(c);

		if (type == "decimals")
		{
			myAllowedCharacters.insert('.');
		}
		if (type == "ip_input")
		{
			myAllowedCharacters.insert('.');
			myAllowedCharacters.insert(':');
		}
	}
}

void CUITextInput::Update()
{
	CInputManager& im = CInputManager::GetInstance();

	if (myIsSelected)
	{
		if (im.IsKeyPressed(EKeyCode::BackSpace))
		{
			std::string currentText = myText.getString();
			myCaretTimer = 0.f;
			myCaretIsVisible = true;
			if (currentText.size() > 0)
			{
				if (im.IsKeyDown(EKeyCode::LeftCtrl) || im.IsKeyDown(EKeyCode::RightCtrl))
				{
					currentText.clear();
					myText.setString(currentText);
				}
				else
				{
					currentText.pop_back();
					myText.setString(currentText);
				}
			}
		}
		else if (im.IsKeyDown(EKeyCode::LeftCtrl) && im.IsKeyPressed(EKeyCode::V))
		{
			std::string input = sf::Clipboard::getString();
			InputString(input);
		}
		else if (!im.IsKeyDown(EKeyCode::BackSpace) && !im.IsKeyDown(EKeyCode::Enter) && !im.IsKeyDown(EKeyCode::Tab))
		{
			std::string input = im.GetTextInput();
			InputString(input);
		}

		myCaret.setPosition(myText.getGlobalBounds().left + myText.getGlobalBounds().width + 2, myText.getPosition().y);
		myCaretTimer += CTime::GetInstance().GetDeltaTime();
		if (myCaretTimer > 0.5f)
		{
			myCaretTimer = 0.f;
			myCaretIsVisible = !myCaretIsVisible;
		}
	}
	else
	{
		myCaretIsVisible = false;
	}

	myText.setPosition(getPosition() + sf::Vector2f(0, myBox.getSize().y / 2.f));

	CUIElement::Update();
}

void CUITextInput::Render(sf::RenderTarget * aTarget)
{
	aTarget->draw(myBox);
	aTarget->draw(myText);

	if (myCaretIsVisible)
	{
		aTarget->draw(myCaret);
	}

	CUIElement::Render(aTarget);
}

std::string CUITextInput::GetText()
{
	return std::move(myText.getString());
}

void CUITextInput::Clear()
{
	myText.setString("");
}

void CUITextInput::InputString(const std::string & aString)
{
	std::string currentText = myText.getString();
	for (char c : aString)
	{
		if (myAllowedCharacters.find(c) == myAllowedCharacters.end())
			break;
		float length = myText.getGlobalBounds().width + myText.getCharacterSize();
		if (length > myBox.getSize().x)
			break;

		currentText += c;
		myText.setString(currentText);
	}
	if (aString.length() > 0)
	{
		myCaretTimer = 0.f;
		myCaretIsVisible = true;
	}
}