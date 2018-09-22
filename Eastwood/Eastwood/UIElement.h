#pragma once
#include <vector>
#include "Graphics/RenderTexture.hpp"
#include "Graphics/Sprite.hpp"
#include "RectangleCollider.h"

#include "JsonDocument.h"

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

	virtual void Init(JsonValue aElementJson);
	virtual void Update();
	virtual void Render(sf::RenderTarget* aTarget);

	CRectangleCollider& GetCollider();
	void AddElement(CUIElement* aElement);
	void SetEventName(const std::string& aEventName);

protected:
	CRectangleCollider myCollider;

	sf::RenderTexture myRenderTexture;
	std::string myName;

private:
	std::string myEventName;
	std::vector<CUIElement*> myChildren;
	bool myWasPressed;
};