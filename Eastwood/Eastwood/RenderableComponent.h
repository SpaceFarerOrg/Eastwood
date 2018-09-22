#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "Component.h"

class CRenderer;

struct SRenderableComponentParam
{
	CRenderer* myRenderer;
	sf::Texture* myTexture;
};

class CRenderableComponent : public CComponent
{
public:
	CRenderableComponent();
	void OnCreated(void* aInParams) override;
	void Tick(float aDT) override;
	void OnDestroy() override;

	ComponentType GetType() const override;
private:
	CRenderer* myRendererToUse;
	sf::Sprite mySprite;

};
