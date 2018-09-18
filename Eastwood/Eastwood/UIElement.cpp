#include "UIElement.h"
#include "InputManager.h"
#include "PointCollider.h"
#include <iostream>
#include "RectangleCollider.h"

CUIElement::CUIElement()
{
}

CUIElement::~CUIElement()
{
}

void CUIElement::Init()
{
	for (CUIElement*& element : myChildren)
	{
		element->Init();
	}

	myRenderTexture.create(1600, 900);
	myCollider = new CRectangleCollider();
	static_cast<CRectangleCollider*>(myCollider)->SetDimensions({ (float)myRenderTexture.getSize().x, (float)myRenderTexture.getSize().y });
}

void CUIElement::Update()
{
	CInputManager& inputManager = CInputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		sf::Vector2f mPos = inputManager.GetMousePosFloat();
		CPointCollider mCollider;
		mCollider.setPosition(mPos);

		if (myCollider->IsColliding(mCollider))
		{
			std::cout << "Pressed " + myEventName << std::endl;
		}
	}

	myCollider->setPosition(getPosition() + static_cast<CRectangleCollider*>(myCollider)->GetDimensions() / 2.f);

	for (CUIElement* element : myChildren)
	{
		element->Update();
	}
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

CCollider * CUIElement::GetCollider()
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
