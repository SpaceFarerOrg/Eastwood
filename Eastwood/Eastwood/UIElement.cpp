#include "UIElement.h"
#include <iostream>
#include "InputManager.h"
#include "PointCollider.h"
#include "RectangleCollider.h"
#include "JsonDocument.h"

#include "UIManager.h"

#include "UISprite.h"
#include "UITextInput.h"

CUIElement::CUIElement()
{
	myDebugMode = false;
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

void CUIElement::SetUIManager(CUIManager * aUIManager)
{
	myUIManagerPtr = aUIManager;
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
		else if (type == "textinput")
		{
			element = new CUITextInput();
		}
		else
		{
			element = new CUIElement();
		}

		element->SetUIManager(myUIManagerPtr);
		element->Init(elementJson);
		AddElement(element);
	}

	myEventName = aElementJson["eventName"].GetString();
	myName = aElementJson["name"].GetString();
	setPosition(aElementJson["x"].GetFloat(), aElementJson["y"].GetFloat());
	myRenderTexture.create(aElementJson["width"].GetInt(), aElementJson["height"].GetInt());
	myCollider.SetDimensions({ (float)myRenderTexture.getSize().x, (float)myRenderTexture.getSize().y });

	randomColor = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
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
		if (childWasPressed)
		{
			myWasPressed = true;
		}
	}

	if (childWasPressed == false && inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		sf::Vector2f mPos = inputManager.GetMousePosFloat();
		CPointCollider mCollider;
		mCollider.setPosition(mPos);

		if (myCollider.IsColliding(mCollider))
		{
			myWasPressed = true;
			myUIManagerPtr->RegisterEvent(myEventName);
			std::cout << "Pressed " + myName + ", Event: " + myEventName << std::endl;
		}
	}

	myCollider.SetDimensions({ (float)myRenderTexture.getSize().x, (float)myRenderTexture.getSize().y });
	myCollider.setPosition(getPosition() + myCollider.GetDimensions() / 2.f);

	if (inputManager.IsKeyPressed(EKeyCode::F3))
	{
		myDebugMode = !myDebugMode;
	}
}

void CUIElement::Render(sf::RenderTarget * aTarget)
{
	if (myDebugMode)
	{
		myRenderTexture.clear(randomColor);
	}

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
