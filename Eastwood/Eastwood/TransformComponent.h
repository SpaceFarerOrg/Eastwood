#pragma once
#include "Component.h"
#include <SFML/Graphics/Transformable.hpp>

class CTransformComponent : public CComponent
{
public:
	CTransformComponent();

	void OnDestroy() override;

	const sf::Vector2f& GetPosition() const;
	void SetPosition(const sf::Vector2f& aNewPosition);
	void Move(const sf::Vector2f& aOffset);

	float GetRotation() const;
	void SetRotation(float aDegrees);
	void Rotate(float aDegreesOffset);
	
	ComponentType GetType() const override;
private:
	sf::Transformable myTransformable;
};
