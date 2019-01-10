#include "Player.h"
#include "MainSingelton.h"
#include "Renderer.h"
#include <iostream>

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	mySpeed = 300.f;
	myTexture.loadFromFile("Graphics/Textures/playerShip.png");
	mySprite.setTexture(myTexture);
	myAccelerationY = 0.f;
}

void CPlayer::Update(float dt)
{
	sf::Vector2f movement = dt * mySpeed * myController.GetDirection();
	movement.y = 0.f;
	if (myController.ShouldJump() && IsGrounded())
	{
		Jump(-20.f);
	}

	myAccelerationY += 50.f / 60.f;
	movement.y = myAccelerationY;
	myTransform.move(movement);

	if (GetTransform().getPosition().y > 400.f)
	{
		myAccelerationY = 0.f;
		GetTransform().setPosition(GetTransform().getPosition().x, 400.f);
	}
	UpdateRenderable();
}

void CPlayer::Render()
{
	CMainSingleton::GetRenderer().PushRenderCommand(mySprite, 0);
}

sf::Transformable & CPlayer::GetTransform()
{
	return myTransform;
}

bool CPlayer::IsGrounded()
{
	return true;
}

void CPlayer::Jump(float aForce)
{
	myAccelerationY = aForce;
}

void CPlayer::UpdateRenderable()
{
	mySprite.setPosition(myTransform.getPosition());
	mySprite.setRotation(myTransform.getRotation());
	mySprite.setScale(myTransform.getScale());
}
