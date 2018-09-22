#include "MenuState.h"
#include <iostream>
#include "InputManager.h"
#include "GameState.h"

CMenuState::CMenuState()
{
}

CMenuState::~CMenuState()
{
	myUIManager.Destroy();
}

void CMenuState::Init()
{
	std::cout << "Pushed MenuState" << std::endl;

	myUIManager.Init("UI/main_menu.json");
}

void CMenuState::Update(float dt)
{
	myUIManager.Update(dt);

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Escape))
	{
		PopAll();
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::F5))
	{
		myUIManager.Destroy();
		myUIManager.Init("UI/main_menu.json");
	}
}

void CMenuState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
