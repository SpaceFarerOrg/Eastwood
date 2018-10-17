#include "Player.h"
#include "MainSingelton.h"
#include "Renderer.h"

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
}

void CPlayer::Update(float dt)
{
	myTransform.move(dt * mySpeed * myController.GetDirection());

	UpdateRenderable();
}

void CPlayer::Render()
{
	CMainSingleton::GetRenderer().PushRenderCommand(mySprite);
}

void CPlayer::UpdateRenderable()
{
	mySprite.setPosition(myTransform.getPosition());
	mySprite.setRotation(myTransform.getRotation());
	mySprite.setScale(myTransform.getScale());
}
