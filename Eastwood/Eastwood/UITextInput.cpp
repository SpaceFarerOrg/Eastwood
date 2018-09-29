#include "UITextInput.h"
#include "InputManager.h"
#include "Time.h"

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
}

void CUITextInput::Update()
{
	CInputManager& im = CInputManager::GetInstance();
	std::string currentText = myText.getString();

	if (myIsSelected)
	{
		if (im.IsKeyPressed(EKeyCode::BackSpace))
		{
			myCaretTimer = 0.f;
			myCaretIsVisible = true;
			if (currentText.size() > 0)
			{
				if (im.IsKeyDown(EKeyCode::LeftCtrl) || im.IsKeyDown(EKeyCode::RightCtrl))
				{
					currentText.clear();
				}
				else
				{
					currentText.pop_back();
				}
			}
		}
		else if (!im.IsKeyDown(EKeyCode::BackSpace) && !im.IsKeyDown(EKeyCode::Enter) && !im.IsKeyDown(EKeyCode::Tab) && myText.getGlobalBounds().width + myText.getCharacterSize() <= myBox.getSize().x)
		{
			std::string input = im.GetTextInput();
			if (input.size() > 0)
			{
				currentText += input;
				myCaretTimer = 0.f;
				myCaretIsVisible = true;
			}
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

	myText.setString(currentText);
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
