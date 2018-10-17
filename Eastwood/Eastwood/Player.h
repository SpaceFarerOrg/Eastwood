#pragma once

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "ControlComponent.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Update(float dt);
	void Render();

private:

	void UpdateRenderable();

	sf::Transformable myTransform;
	sf::Sprite mySprite;
	sf::Texture myTexture;
	CControlComponent myController;

	float mySpeed;
};