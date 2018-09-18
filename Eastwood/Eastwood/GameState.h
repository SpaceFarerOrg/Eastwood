#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "SFML/Graphics/Texture.hpp"

class CGameState : public CState
{
public:
	CGameState();
	~CGameState();

	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* aRenderWindow) override;
private:
	unsigned int myTestGameObject;
	sf::Texture myTestTexture;
	CObjectManager myObjectManager;
	CRenderer myRenderer;
};

