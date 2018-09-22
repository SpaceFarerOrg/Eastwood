#include "UIElement.h"
#include "InputManager.h"
#include "PointCollider.h"
#include <iostream>
#include "RectangleCollider.h"

#include "JsonDocument.h"

#include "UISprite.h"

CUIElement::CUIElement()
{
}

CUIElement::~CUIElement()
{
}

void CUIElement::Destroy()
{
	for (CUIElement* child : myChildren)
	{
		child->Destroy();
		delete child;
	}
	myChildren.clear();
}

void CUIElement::Init(JsonValue aElementJson)
{
	auto elementList = aElementJson["elements"];
	for (int i = 0; i < elementList.GetSize(); ++i)
	{
		JsonValue elementJson = elementList[i];
		CUIElement* element = nullptr;

		std::string type = elementJson["type"].GetString();

		if (type == "")
		{
			element = new CUIElement();
		}
		else if (type == "sprite")
		{
			element = new CUISprite();
		}
		else
		{
			element = new CUIElement();
		}

		element->Init(elementJson);
		AddElement(element);
	}

	myName = aElementJson["name"].GetString();
	setPosition(aElementJson["x"].GetFloat(), aElementJson["y"].GetFloat());
	myRenderTexture.create(aElementJson["width"].GetInt(), aElementJson["height"].GetInt());
}

void CUIElement::Update()
{
	CInputManager& inputManager = CInputManager::GetInstance();
	myWasPressed = false;

	bool childWasPressed = false;
	for (CUIElement* element : myChildren)
	{
		element->Update();
		childWasPressed = element->myWasPressed ? true : childWasPressed;
	}

	if (childWasPressed == false && inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		sf::Vector2f mPos = inputManager.GetMousePosFloat();
		CPointCollider mCollider;
		mCollider.setPosition(mPos);

		if (myCollider.IsColliding(mCollider))
		{
			myWasPressed = true;
			std::cout << "Pressed " + myName + ", Event: " + myEventName << std::endl;
		}
	}

	myCollider.SetDimensions({ (float)myRenderTexture.getSize().x, (float)myRenderTexture.getSize().y });
	myCollider.setPosition(getPosition() + myCollider.GetDimensions() / 2.f);
}

void CUIElement::Render(sf::RenderTarget * aTarget)
{
	for (CUIElement*& element : myChildren)
	{
		element->Render(&myRenderTexture);
	}
	myRenderTexture.display();
	setTexture(myRenderTexture.getTexture());

	aTarget->draw(*this);
}

CRectangleCollider& CUIElement::GetCollider()
{
	return myCollider;
}

void CUIElement::AddElement(CUIElement * aElement)
{
	myChildren.push_back(aElement);
}

void CUIElement::SetEventName(const std::string & aEventName)
{
	myEventName = std::move(aEventName);
}
