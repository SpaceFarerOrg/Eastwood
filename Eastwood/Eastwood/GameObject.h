#pragma once
#include "ObjectManager.h"
#include "SFML/Graphics/Transformable.hpp"

class CGameObject
{
public:
	CGameObject() = delete;
	CGameObject(CObjectManager& aObjectManager ,unsigned int aGameObjectID);
	
	//BEGIN OBJECT SPECIFICS
	void OnDestroy();
	unsigned int GetGameObjectID() const;
	void AddComponent(const CComponent& aNewComponent, void* aComponentCreationParams = nullptr) const;
	//END OBJECT SPECIFICS

	//BEGIN TRANSFORM
	void SetPosition(const sf::Vector2f& aPosition);
	const sf::Vector2f& GetPosition() const;
	void Move(const sf::Vector2f& aMove);

	void SetRotation(float aNewRotation);
	float GetRotation() const;
	void Rotate(float aRotation);
	//END TRANSFORM

private:
	CObjectManager& myObjectManager;
	unsigned int myGameObjectID;
	
	sf::Transformable myTransform;
};

