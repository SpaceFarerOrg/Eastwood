#include "GameState.h"
#include "InputManager.h"
#include <iostream>
#include "MenuState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "RenderableComponent.h"

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

void CGameState::Init()
{
	std::cout << "Pushed GameState" << std::endl;

	myTestTexture.loadFromFile("playerShip.png");

	myObjectManager.Initialize(512);

	myTestGameObject = myObjectManager.CreateGameObject().GetGameObjectID();
	CGameObject& object = myObjectManager.GetGameObject(myTestGameObject);

	SRenderableComponentParam renderableCompData;
	renderableCompData.myRenderer = &myRenderer;
	renderableCompData.myTexture = &myTestTexture;

	object.AddComponent(CRenderableComponent(), &renderableCompData);

	myObjectManager.BeginPlay();
}

void CGameState::Update(float dt)
{
	myObjectManager.Tick(dt);

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Escape))
	{
		PopAll();
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::BackSpace))
	{
		if (Pop())
		{
			std::cout << "Popped GameState" << std::endl;
		}
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::M))
	{
		Push(new CMenuState());
	}
}

void CGameState::Render(sf::RenderWindow * aRenderWindow)
{
	if (!myRenderer.IsCreated())
	{
		myRenderer.Create(aRenderWindow->getSize().x, aRenderWindow->getSize().y);
	}

	sf::Sprite renderedImage = myRenderer.RunRendering();
	aRenderWindow->draw(renderedImage);

	myRenderer.Clear();
}
