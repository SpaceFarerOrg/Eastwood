#pragma once
#include <vector>
#include "Graphics/RenderTexture.hpp"
#include "Graphics/Sprite.hpp"
#include "RectangleCollider.h"

#include "JsonDocument.h"

class CUIManager;

namespace sf
{
	class RenderTarget;
}

class CUIElement : public sf::Sprite
{
public:
	CUIElement();
	virtual ~CUIElement();

	void Destroy();
	void SetUIManager(CUIManager* aUIManager);

	virtual void Init(JsonValue aElementJson);
	virtual void Update();
	virtual void Render(sf::RenderTarget* aTarget);

	CRectangleCollider& GetCollider();
	void AddElement(CUIElement* aElement);
	void SetEventName(const std::string& aEventName);

	void Deselect();

	template<typename T>
	T* FindElement(const std::string& aElementName);

protected:
	CRectangleCollider myCollider;

	std::string myName;
	bool myIsSelected;

private:
	CUIManager* myUIManagerPtr;

	std::string myEventName;
	std::vector<CUIElement*> myChildren;
	bool myWasPressed;

	bool myDebugMode;
	sf::Color randomColor;
};

template<typename T>
inline T * CUIElement::FindElement(const std::string & aElementName)
{
	// See if element is one of my children
	for (CUIElement* child : myChildren)
	{
		if (child->myName == aElementName)
		{
			T* element = dynamic_cast<T*>(child);
			if (element == nullptr)
			{
				std::cout << "Found the element but the dynamic_cast returned nullptr." << std::endl;
			}
			return element;
		}
	}

	// See if element is in one of my children
	T* element = nullptr;
	for (CUIElement* child : myChildren)
	{
		element = child->FindElement<T>(aElementName);
	}
	return element;
}
