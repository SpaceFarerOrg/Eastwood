#include "TransformComponent.h"

CTransformComponent::CTransformComponent()
	: CComponent(this, sizeof(CTransformComponent))
{
}

//-----------------------------------------------------------

void CTransformComponent::OnDestroy()
{

}

//-----------------------------------------------------------

const sf::Vector2f& CTransformComponent::GetPosition() const
{
	return myTransformable.getPosition();
}

//-----------------------------------------------------------

void CTransformComponent::SetPosition(const sf::Vector2f & aNewPosition)
{
	myTransformable.setPosition(aNewPosition);
}

//-----------------------------------------------------------

void CTransformComponent::Move(const sf::Vector2f & aOffset)
{
	myTransformable.move(aOffset);
}

//-----------------------------------------------------------

float CTransformComponent::GetRotation() const
{
	return myTransformable.getRotation();
}

//-----------------------------------------------------------

void CTransformComponent::SetRotation(float aDegrees)
{
	myTransformable.setRotation(aDegrees);
}

//-----------------------------------------------------------

void CTransformComponent::Rotate(float aDegreesOffset)
{
	myTransformable.rotate(aDegreesOffset);
}

//-----------------------------------------------------------

ComponentType CTransformComponent::GetType() const
{
	return typeid(CTransformComponent);
}
