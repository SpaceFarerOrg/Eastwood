#pragma once
#include <vector>
#include "Graphics/RenderTexture.hpp"
#include "Graphics/Sprite.hpp"
#include "Collider.h"

namespace sf
{
	class RenderTarget;
}

class CUIElement : public sf::Sprite
{
public:
	CUIElement();
	~CUIElement();

	virtual void Init(/*Json here, things like position and size*/);
	virtual void Update();
	virtual void Render(sf::RenderTarget* aTarget);

	CCollider* GetCollider();
	void AddElement(CUIElement* aElement);

private:
	CCollider* myCollider;

	sf::RenderTexture myRenderTexture;
	std::string myEventName;
	std::vector<CUIElement*> myChildren;
};