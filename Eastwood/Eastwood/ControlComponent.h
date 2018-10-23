#pragma once

#include "SFML/System/Vector2.hpp"

class CControlComponent
{
public:

	bool ShouldJump();
	sf::Vector2f GetDirection();
};